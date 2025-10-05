#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	Texture() { };
	Texture(std::string file);
	~Texture();

	void Bind(unsigned int id);

private:
	unsigned int texture;
};


#endif // !TEXTURE_H
