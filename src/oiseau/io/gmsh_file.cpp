#include <charconv>
#include <fstream>
#include <oiseau/io/gmsh_file.hpp>
#include <oiseau/utils/logging.hpp>
#include <string_view>

#define PREFIX '$'

namespace {
using namespace oiseau::io;

const std::size_t gmsh_nodes_per_cell(const std::size_t s) {
  if (s == 1)  // line
    return 2;
  else if (s == 2)  // triangle
    return 3;
  else if (s == 3)  // quad
    return 4;
  else if (s == 4)  // tetra
    return 4;
  else if (s == 5)  // hexahedron
    return 8;
  else if (s == 6)  // hexahedron
    return 6;
  else if (s == 7)  // wedge
    return 5;
  else
    throw std::runtime_error("Unknown cell type");
}

template <class T>
concept Readable = std::is_convertible_v<T, std::string_view> || std::is_arithmetic_v<T>;

template <int N, Readable T>
std::array<T, N> from_file(std::istream& f) {
  std::array<T, N> arr;
  if constexpr (std::is_arithmetic_v<T>) {
    std::string entry;
    for (std::size_t i = 0; i < N; i++) {
      f >> entry;
      std::from_chars(entry.data(), entry.data() + entry.size(), arr[i]);
    }
  } else {
    for (std::size_t i = 0; i < N; i++) f >> arr.at(i);
  }
  return arr;
}

template <Readable T>
std::vector<T> from_file(std::istream& f, int n) {
  std::vector<T> vec(n);
  if constexpr (std::is_arithmetic_v<T>) {
    std::string entry;
    for (std::size_t i = 0; i < n; i++) {
      f >> entry;
      std::from_chars(entry.data(), entry.data() + entry.size(), vec.at(i));
    }
  } else {
    for (std::size_t i = 0; i < n; i++) {
      f >> vec.at(i);
    }
  }
  return vec;
}

template <int N, Readable T>
std::array<T, N> split_to_array(std::string_view s) requires std::is_arithmetic_v<T> {
  std::array<T, N> arr;
  std::size_t pos = 0, index = 0;
  while (pos < s.size() && index < N) {
    const std::size_t found_index = s.find_first_of(' ', pos);
    const std::size_t last = found_index < s.size() ? found_index : s.size();
    if constexpr (std::is_arithmetic_v<T>)
      std::from_chars(s.data() + pos, s.data() + last - pos, arr[index]);
    else
      arr.at(index) = std::string(s.data() + pos, s.data() + last - pos);
    index++;
    pos = last + 1;
  }
  return arr;
}

MeshFormatSection mesh_format_handler(std::fstream& f_handler) {
  auto [version] = from_file<1, double>(f_handler);
  auto [is_ascii] = from_file<1, int>(f_handler);
  auto [data_size] = from_file<1, std::size_t>(f_handler);
  return MeshFormatSection(version, is_ascii, data_size);
};

PhysicalNamesSection physical_names_handler(std::istream& f_handler) {
  auto [num_phys_names] = from_file<1, int>(f_handler);
  std::vector<int> dimensions;
  std::vector<int> physical_tags;
  std::vector<std::string> names;
  dimensions.reserve(num_phys_names);
  physical_tags.reserve(num_phys_names);
  names.reserve(num_phys_names);
  for (int i = 0; i < num_phys_names; i++) {
    auto [dim, tag] = from_file<2, int>(f_handler);
    auto [name] = from_file<1, std::string>(f_handler);
    dimensions.emplace_back(dim);
    physical_tags.emplace_back(tag);
    names.emplace_back(name);
  }
  return PhysicalNamesSection(num_phys_names, std::move(dimensions), std::move(physical_tags),
                              std::move(names));
};

EntitiesSection entities_handler(std::istream& f_handler) {
  auto quantity = from_file<4, int>(f_handler);
  std::array<std::vector<EntityEntry>, 4> blocks;
  for (std::size_t i = 0; i < 4; i++) blocks.at(i).reserve(quantity.at(i));
  for (int d = 0; d < 4; d++) {
    for (int j = 0; j < quantity[d]; j++) {
      auto [tag] = from_file<1, int>(f_handler);
      auto bounding_coods = from_file<double>(f_handler, (d == 0) ? 3 : 6);
      auto [num_physicals] = from_file<1, int>(f_handler);
      auto physical_tags = from_file<int>(f_handler, num_physicals);
      if (d > 0) {
        auto [num_BREP] = from_file<1, int>(f_handler);
        auto bounding_entities = from_file<int>(f_handler, num_BREP);
        blocks.at(d).emplace_back(tag, std::move(bounding_coods), std::move(physical_tags),
                                  std::move(bounding_entities));
      } else {
        blocks.at(d).emplace_back(tag, std::move(bounding_coods), std::move(physical_tags));
      }
    }
  }
  return EntitiesSection(std::move(blocks));
};

NodesSection nodes_handler(std::istream& f_handler) {
  auto [num_entity_blocks, total_num_nodes, min_node_tag, max_node_tag] =
      from_file<4, int>(f_handler);

  std::vector<NodesBlock> blocks;
  blocks.reserve(num_entity_blocks);

  for (int i = 0; i < num_entity_blocks; i++) {
    auto [dim, entity_tag, parametric, quantity] = from_file<4, int>(f_handler);
    std::vector<std::size_t> node_tags;
    std::vector<double> node_coords;
    node_tags.reserve(quantity);
    node_coords.reserve(quantity * 3);

    for (int j = 0; j < quantity; j++) {
      auto [tag] = from_file<1, int>(f_handler);
      node_tags.emplace_back(tag);
    }
    for (int j = 0; j < quantity; j++) {
      auto xyz = from_file<3, double>(f_handler);
      node_coords.insert(node_coords.end(), xyz.begin(), xyz.end());
    }
    blocks.emplace_back(dim, entity_tag, parametric, quantity, std::move(node_tags),
                        std::move(node_coords));
  }
  return NodesSection(num_entity_blocks, total_num_nodes, min_node_tag, max_node_tag,
                      std::move(blocks));
};

ElementSection elements_handler(std::istream& f_handler) {
  auto [num_element_blocks, num_elements, min_element_tag, max_element_tag] =
      from_file<4, std::size_t>(f_handler);
  std::vector<ElementBlock> blocks;
  blocks.reserve(num_element_blocks);
  for (std::size_t i = 0; i < num_element_blocks; i++) {
    auto [entity_dim, entity_tag] = from_file<2, int>(f_handler);
    auto [element_type, num_elements_in_block] = from_file<2, std::size_t>(f_handler);
    auto size = gmsh_nodes_per_cell(element_type);
    auto tmp_conn = from_file<std::size_t>(f_handler, (1 + size) * num_elements_in_block);
    blocks.emplace_back(entity_dim, entity_tag, element_type, num_elements_in_block,
                        std::move(tmp_conn));
  }
  return ElementSection(num_element_blocks, num_elements, min_element_tag, max_element_tag,
                        std::move(blocks));
};

void skip_to_end_of_enviroment(std::fstream& f_handler) {
  std::string line;
  while (getline(f_handler, line)) {
    if (line.starts_with(PREFIX)) break;
  }
}

}  // namespace

void oiseau::io::GMSHFile::read(const std::string& filename) {
  std::fstream f_handler;
  f_handler.open(filename, std::ios::in);
  if (f_handler.fail()) throw std::runtime_error("Could not open file");
  std::string line;
  while (getline(f_handler, line)) {
    if (line.starts_with(PREFIX)) {
      line = line.substr(1);
      if (line == "MeshFormat") {
        mesh_format_section = mesh_format_handler(f_handler);
      } else if (line == "PhysicalNames") {
        physical_names_section = physical_names_handler(f_handler);
      } else if (line == "Entities") {
        entities_section = entities_handler(f_handler);
      } else if (line == "Nodes") {
        nodes_section = nodes_handler(f_handler);
      } else if (line == "Elements")
        elements_section = elements_handler(f_handler);
      skip_to_end_of_enviroment(f_handler);
    }
  }
  if (f_handler.is_open()) f_handler.close();
}
