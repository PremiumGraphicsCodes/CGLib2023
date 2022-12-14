#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Graphics/ColorRGBA.h"
#include <istream>
#include <sstream>
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

		class Helper {
		public:
			template<typename T>
			static T read(std::istream& s)
			{
				T val;
				s >> val;
				return val;
			}

			template<typename T>
			static Math::Vector3dd readVector(std::istream& s)
			{
				T x, y, z;
				s >> x >> y >> z;
				return Math::Vector3dd(x, y, z);
			}

			static Graphics::ColorRGBAf readColorRGB(std::istream& s)
			{
				float r, g, b;
				s >> r >> g >> b;
				return Graphics::ColorRGBAf(r, g, b, 0.0f);
			}


			static Graphics::ColorRGBAf readColorRGBA(std::istream& s)
			{
				float r, g, b, a;
				s >> r >> g >> b >> a;
				return Graphics::ColorRGBAf(r, g, b, a);
			}

			static std::string readNextString(std::istream& stream)
			{
				std::string str = read<std::string>(stream);
				const int size = -static_cast<int>(str.size());
				stream.seekg(size, std::ios_base::cur);
				return str;
			}

			static std::vector< std::string > split(const std::string& str, char delim) {
				/*std::istringstream iss(str);
				std::string tmp;
				std::vector< std::string > res;
				while( getline(iss, tmp, delim) ) {
				res.push_back(tmp);
				}
				return res;*/
				//int a = str.find( delim );
				std::vector< std::string > res;
				std::string tmp;
				for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter) {
					if (*iter != delim) {
						tmp += *iter;
					}
					else {
						if (!tmp.empty()) {
							res.push_back(tmp);
						}
						tmp.clear();
					}
				}
				res.push_back(tmp);
				return res;
			}

		};

	}
}
