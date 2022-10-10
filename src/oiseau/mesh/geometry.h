namespace oiseau::mesh {
class Geometry {
  public:
    Geometry();
    Geometry(Geometry &&) = default;
    Geometry(const Geometry &) = default;
    Geometry &operator=(Geometry &&) = default;
    Geometry &operator=(const Geometry &) = default;
    ~Geometry();
};
} // namespace oiseau::mesh
