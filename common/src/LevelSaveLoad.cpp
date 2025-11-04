#include "LevelSaveLoad.hpp"

//stored as little endian with a being the significant 
inline qword_t floatPairToQword(const float a, const float b) {
	qword_t intergralA = floatToDword(a);
	dword_t intergralB = floatToDword(b);
	return (static_cast<qword_t>(intergralA) << sizeof(float)) & intergralB;
}

dword_t getAmountOfBytesInImage(const sf::Image& image) {
	const qword_t bytesInImg = static_cast<qword_t>(image.getSize().x) * image.getSize().y * sizeof(sf::Color);
	if (bytesInImg > std::numeric_limits<dword_t>::max())
		throw std::runtime_error("error, image is too large\n");
	return static_cast<dword_t>(bytesInImg);
}

dword_t getThumbSize(const SerializedLevelWrite& lev) {
	const dword_t bytesInImg = getAmountOfBytesInImage(lev.thumbnail);
	const dword_t sizeSpecifiers = sizeof(byte_t) + sizeof(dword_t);
	return lev.name.length() + bytesInImg + sizeSpecifiers;
}

dword_t getLevelSize(const SerializedLevelWrite& lev) {
	const dword_t pegBytes = static_cast<dword_t>(lev.pegs.size() * sizeof(*lev.pegs.data()));
	const dword_t bytesInImage = getAmountOfBytesInImage(lev.background);
	const dword_t sizeSpecifiers = sizeof(word_t) + sizeof(dword_t);
	return pegBytes + bytesInImage + sizeSpecifiers;
}

void writeImage(std::fstream& file, const sf::Image& image) {
	const dword_t amountOfBytesInImg = getAmountOfBytesInImage(image);
	const sf::Uint8* imgBytes = image.getPixelsPtr();

	fileStream::write<dword_t>(file, amountOfBytesInImg);
	for (dword_t imgByteIndex = 0; imgByteIndex < amountOfBytesInImg; imgByteIndex++)
		fileStream::write<byte_t>(file, static_cast<byte_t>(imgBytes[imgByteIndex]));
}

void writePeg (std::fstream& file, const SerializedPeg& peg) {
	fileStream::write<qword_t>(file, floatPairToQword(peg.position.x, peg.position.y));
	fileStream::write<qword_t>(file, floatPairToQword(peg.size.x, peg.size.y));
	fileStream::write<dword_t>(file, floatToDword(peg.rotation));
	fileStream::write<byte_t>(file, static_cast<unsigned char>(peg.shape));
};

//TODO, write image
std::pair<std::vector<SerializedLevelRead>, bool> loadSerializedLevels(const std::string& path) {
	return {};
}
