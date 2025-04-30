import oiseau.mesh

triangle = oiseau.mesh.get_cell_type("triangle")
vertices = triangle.get_entity_vertices(1)
print(vertices)
