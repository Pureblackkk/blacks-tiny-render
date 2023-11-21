#include<loader.h>

int Loader::loadGeometry(Geometry &geo, const std::string filename) {
    std::ifstream inputFile(filename);

    // Throw error when failed to open
    if(!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return 1;
    }

    // Read lines
    std::string line;
    while(std::getline(inputFile, line)) {
        std::string symbol;
        std::istringstream lineStream(line.c_str());

        lineStream >> symbol;

        if(symbol == "v") {
            Vector3f v;
            lineStream >> v.x >> v.y >> v.z;
            geo.verts.push_back(v);
        } else if(symbol == "vt") {
            Vector2f vt;
            lineStream >> vt.x >> vt.y;
            geo.tex_coord.push_back(vt);
        } else if(symbol == "vn") {
            Vector3f vn;
            lineStream >> vn.x >> vn.y >> vn.z;
            geo.norms.push_back(vn);
        } else if(symbol == "f") {
            Vector3f f;
            int v, t, n;
            char split;
            int count = 0;
            while (lineStream >> v >> split >> t >> split >> n) {
                geo.facet_vrt.push_back(--v);
                geo.facet_tex.push_back(--t);
                geo.facet_tex.push_back(--n);
                count += 1;
            }

            // Only support triangulated obj file
            if (3 != count) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return 1;
            }
        }
    }
    return 0;
}