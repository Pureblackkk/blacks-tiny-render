#include<loader.h>

bool Loader::loadGeometry(Geometry &geo, const std::string filename, bool isCalculateTangentAndBITangent) {
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
            geo.tex_coords.push_back(vt);
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
                geo.facet_nrm.push_back(--n);
                count += 1;
            }

            // Only support triangulated obj file
            if (3 != count) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return 1;
            }
        }
    }

    if (isCalculateTangentAndBITangent) {
        geo.calculateTangentAndBITangent();
    }

    return 0;
}

bool Loader::loadTexture(Image &img, const char *filename) {
    bool isSuccess = img.read_file(filename);
    // Reverse uv coordinates 
    img.flip_vertically();
    return isSuccess;
}

bool Loader::loadTexture(Image **img, const std::string filename) {
    bool isSuccess = false;

    // Initialize instance based on file suffixes
    if(hasSuffix(filename, ".tga")) {
        TGAImage *newInstance = new TGAImage();
        isSuccess = newInstance->read_file(filename.c_str());
        newInstance->flip_vertically();
        *img = newInstance;
    } else if (hasSuffix(filename, ".png")) {
        PNGImage *newInstance = new PNGImage();
        isSuccess = newInstance->read_file(filename.c_str());
        *img = newInstance;
    } else {
        throw std::runtime_error("Load texture failed, wrong texture format");
        return isSuccess;
    }

    return isSuccess;
}

bool Loader::hasSuffix(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }

    std::string strSuffix = str.substr(str.length() - suffix.length());
    return strSuffix == suffix;
}

