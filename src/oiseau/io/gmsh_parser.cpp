#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <oiseau/io/gmsh_parser.hpp>
#include <string>
#include <string_view>
#include <vector>

#define PREFIX '$'

namespace {
unsigned gmsh_nodes_per_cell(const unsigned s) {
  switch (s) {
  case 1:
    return 2;  // line
    break;
  case 2:
    return 3;  // triangle
    break;
  case 3:
    return 4;  // quad
    break;
  case 4:
    return 4;  // tetra
    break;
  case 5:
    return 8;  // hexahedron
    break;
  case 6:
    return 6;  // wedge
    break;
  case 7:
    return 5;  // pydramid
    break;
  default:
    throw std::runtime_error("Unknown cell type");
  }
}

template <class T>
concept Readable = std::is_convertible_v<T, std::string_view> || std::is_arithmetic_v<T>;

void skip_to_end_of_enviroment(std::fstream& f_handler) {
  std::string line;
  while (getline(f_handler, line)) {
    if (line.starts_with(PREFIX)) break;
  }
}

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

void mesh_format_handler(std::fstream& f_handler) {
  auto [version] = from_file<1, std::string>(f_handler);
  auto [is_ascii, data_size] = from_file<2, int>(f_handler);
  // std::cout << "version: " << version << std::endl;
};
void physical_names_handler(std::fstream& f_handler) {
  auto [num_phys_names] = from_file<1, int>(f_handler);
  // std::cout << "num_phys_names: " << num_phys_names << std::endl;
  for (int i = 0; i < num_phys_names; i++) {
    auto [dim, group_id] = from_file<2, int>(f_handler);
    auto [group_name] = from_file<1, std::string>(f_handler);
    // std::cout << "dim: " << dim << " g_id: " << group_id << " g_name: " << group_name <<
    // std::endl;
  }
};

// template <typename T, class Container>
// std::ostream& operator<<(std::ostream& os, Container& v) {
//   if (!v.empty()) {
//     os << '[';
//     std::ranges::copy(v, std::ostream_iterator<typename Container::type_value>(os, ", "));
//     os << "\b\b]";
//   }
//   return os;
// }

void entities_handler(std::fstream& f_handler) {
  std::string line;
  auto quantity = from_file<4, int>(f_handler);
  for (int d = 0; d < 4; d++) {
    for (int j = 0; j < quantity[d]; j++) {
      auto [tag] = from_file<1, int>(f_handler);
      // std::cout << "tag: " << tag << " ";
      // std::cout << "boundary: ";
      if (d == 0) {
        auto vec = from_file<3, double>(f_handler);
        for (double e : vec) {
          // std::cout << e << " ";
        }
      } else {
        auto vec = from_file<6, double>(f_handler);
        for (double e : vec) {
          // std::cout << e << " ";
        }
      }
      auto [num_physicals] = from_file<1, int>(f_handler);
      // std::cout << "num_physicals: " << num_physicals << " ";
      // std::cout << std::flush;
      auto physical_tags = from_file<int>(f_handler, num_physicals);
      if (d > 0) {
        auto [num_BREP] = from_file<1, int>(f_handler);
        auto vecs = from_file<int>(f_handler, num_BREP);
      }
      // std::cout << std::endl;
    }
  }
};

std::vector<double> nodes_handler(std::fstream& f_handler) {
  auto [num_entity_blocks, total_num_nodes, _, __] = from_file<4, int>(f_handler);
  std::cout << "num_entity_blocks: " << num_entity_blocks << std::endl;
  std::cout << "total_num_nodes: " << total_num_nodes << std::endl;
  std::vector<double> nodes;
  nodes.reserve(total_num_nodes * 3);
  for (int i = 0; i < num_entity_blocks; i++) {
    auto [dim, entity_tag, parametric, quantity] = from_file<4, int>(f_handler);
    for (int j = 0; j < quantity; j++) {
      auto [tag] = from_file<1, int>(f_handler);
    }
    for (int j = 0; j < quantity; j++) {
      auto xyz = from_file<3, double>(f_handler);
      nodes.insert(nodes.end(), xyz.begin(), xyz.end());
    }
  }
  return nodes;
};

void elements_handler(std::fstream& f_handler) {
  auto [num_element_blocks, _, __, ___] = from_file<4, int>(f_handler);
  std::string line;
  for (int i = 0; i < num_element_blocks; i++) {
    auto [dim, etag, element_type, num_elements] = from_file<4, int>(f_handler);
    // std::cout << "dim: " << dim << " tag: " << etag << " element_type: " << element_type
    //           << " num_elements: " << num_elements << std::endl;
    for (int j = 0; j < num_elements; j++) {
      auto size = gmsh_nodes_per_cell(element_type);
      auto [tag] = from_file<1, int>(f_handler);
      auto vec = from_file<int>(f_handler, size);
      // std::cout << "tag: " << tag << std::endl;
      // for (auto e : vec) {
      //   std::cout << e << " ";
      // }
      // std::cout << std::endl;

      // std::cout << "size: " << size << std::endl;
      // std::getline(f_handler, line);
      // if (line.empty()) {
      //   j--;
      //   continue;
      // }
      // std::cout << line << std::endl;
      // auto [node1, node2, node3, node4] = from_file<4, int>(f_handler);
      // std::cout << node1 << " " << node2 << " " << node3 << " " << node4 << std::endl;
    }
  }
};
}  // namespace

void oiseau::io::parse() {
  std::fstream f_handler;
  f_handler.open("mesh.msh", std::ios::in);
  std::vector<double> nodes;
  if (f_handler.is_open()) {
    std::string line;
    while (getline(f_handler, line)) {
      if (line.starts_with(PREFIX)) {
        line = line.substr(1);
        if (line == "MeshFormat") {
          mesh_format_handler(f_handler);
        } else if (line == "PhysicalNames") {
          physical_names_handler(f_handler);
        } else if (line == "Entities") {
          // entities_handler(f_handler);
        } else if (line == "Nodes") {
          nodes = nodes_handler(f_handler);
        } else if (line == "Elements")
          elements_handler(f_handler);
        skip_to_end_of_enviroment(f_handler);
      }
    }
    f_handler.close();
  }
}
