import gmsh
import sys


def main():
    gmsh.initialize()
    gmsh.model.add("mesh3d_tetra_block")

    gmsh.option.setNumber("Mesh.CharacteristicLengthMin", 1.00)

    gmsh.model.occ.addBox(0, 0, 0, 1, 1, 1)
    gmsh.model.occ.synchronize()
    gmsh.model.mesh.generate(3)

    gmsh.write("mesh3d_tetra_block.msh")

    if "-nopopup" not in sys.argv:
        gmsh.fltk.run()

    gmsh.finalize()


if __name__ == "__main__":
    main()
