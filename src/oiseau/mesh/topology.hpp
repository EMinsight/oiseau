namespace oiseau::mesh {

class Topology {
 public:
  Topology();
  Topology(Topology &&) = default;
  Topology(const Topology &) = default;
  Topology &operator=(Topology &&) = default;
  Topology &operator=(const Topology &) = default;
  ~Topology();
};

}  // namespace oiseau::mesh
