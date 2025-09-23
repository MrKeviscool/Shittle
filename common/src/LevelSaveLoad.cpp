#include "LevelSaveLoad.hpp"

#include <limits>

#include "FileStreamCommon.hpp"

//stored as little endian with a being the significant 
static inline qword_t floatPairToQword(const float a, const float b) {
	qword_t intergralA = floatToDword(a);
	dword_t intergralB = floatToDword(b);
	return (static_cast<qword_t>(intergralA) << sizeof(float)) & intergralB;
}

static dword_t getBytesInImage(const sf::Image& image) {
	const qword_t bytesInImg = static_cast<qword_t>(image.getSize().x) * image.getSize().y * sizeof(sf::Color);
	if (bytesInImg > std::numeric_limits<dword_t>::max())
		throw std::runtime_error("error, image is too large\n");
	return static_cast<dword_t>(bytesInImg);
}

inline static dword_t getThumbSize(const SerializedLevelWrite& lev) {
	const dword_t bytesInImg = getBytesInImage(lev.thumbnail);
	const dword_t sizeSpecifiers = sizeof(byte_t) + sizeof(dword_t);
	return lev.name.length() + bytesInImg + sizeSpecifiers;
}

static dword_t getLevelSize(const SerializedLevelWrite& lev) {
	const dword_t pegBytes = static_cast<dword_t>(lev.pegs.size() * sizeof(*lev.pegs.data()));
	const dword_t bytesInImage = getBytesInImage(lev.background);
	const dword_t sizeSpecifiers = sizeof(word_t) + sizeof(dword_t);
	return pegBytes + bytesInImage + sizeSpecifiers;
}

static dword_t getTotalThumbnailsSize(const std::vector<SerializedLevelWrite>& levels) {
	dword_t size = 0;
	for(const auto& lev : levels)
		size += getThumbSize(lev);
	return size;
}

static dword_t writeAmountOfLevels(std::fstream& file, const std::vector<SerializedLevelWrite>& levels, const dword_t curOffset = 0) {
	fileStream::write<word_t>(file, static_cast<word_t>(levels.size()));
	return curOffset + sizeof(word_t);
}

static dword_t writeThumbnailOffsets(std::fstream& file, const std::vector<SerializedLevelWrite>& levels, dword_t curOffset) {
	curOffset += static_cast<dword_t>((levels.size() * sizeof(dword_t)) + 1);

	for (const auto& lev : levels) {
		fileStream::write<dword_t>(file, curOffset);
		curOffset += getThumbSize(lev);
	}

	return curOffset;
}

static dword_t writeLevelOffsets(std::fstream& file, const std::vector<SerializedLevelWrite>& levels, dword_t curOffset) {
	curOffset += static_cast<dword_t>(levels.size() * sizeof(dword_t) + 1);

	for (const auto& lev : levels) {
		fileStream::write<dword_t>(file, curOffset);
		curOffset += getLevelSize(lev);
	}
	return curOffset;
}

static void writeImage(std::fstream& file, const sf::Image& image) {
	const dword_t amountOfBytesInImg = getBytesInImage(image);
	const sf::Uint8* imgBytes = image.getPixelsPtr();

	fileStream::write<dword_t>(file, amountOfBytesInImg);
	for (dword_t imgByteIndex = 0; imgByteIndex < amountOfBytesInImg; imgByteIndex++)
		fileStream::write<byte_t>(file, static_cast<byte_t>(imgBytes[imgByteIndex]));
}

static void writeThumbnails(std::fstream& file, const std::vector<SerializedLevelWrite>& levels) {
	for (const auto& lev : levels) {

		const dword_t amountOfBytesInImg = getBytesInImage(lev.thumbnail);

		fileStream::write<byte_t>(file, static_cast<byte_t>(lev.name.size()));
		for (const auto let : lev.name)
			fileStream::write<decltype(let)>(file, let);

		writeImage(file, lev.thumbnail);
	}
}

static void writePeg (std::fstream& file, const SerializedPeg& peg) {
	fileStream::write<qword_t>(file, floatPairToQword(peg.position.x, peg.position.y));
	fileStream::write<qword_t>(file, floatPairToQword(peg.size.x, peg.size.y));
	fileStream::write<dword_t>(file, floatToDword(peg.rotation));
	fileStream::write<byte_t>(file, static_cast<unsigned char>(peg.shape));
};

//TODO, write image
static void writeLevels(std::fstream& file, const std::vector<SerializedLevelWrite>& levels) {
	constexpr const size_t pegSize = sizeof(SerializedPeg);
	for (const auto& lev : levels) {
		fileStream::write<word_t>(file, lev.pegs.size()); //write amount of pegs
		for (const auto& peg : lev.pegs) //write pegs
			writePeg(file, peg);
		writeImage(file, lev.background);
	}
}

bool saveLevel(const std::string& path, const std::vector<SerializedLevelWrite>& levels) {
	std::fstream file(path, std::ios_base::out);

	if (!file.is_open())
		return false;

	{
		dword_t curOffset = 0;
		curOffset += writeAmountOfLevels(file, levels, curOffset);
		curOffset += writeThumbnailOffsets(file, levels, curOffset);
		writeLevelOffsets(file, levels, curOffset);
	}
	
	writeThumbnails(file, levels);
	writeLevels(file, levels);

	return true;
}

std::pair<std::vector<SerializedLevelRead>, bool> loadLevels(const std::string& path) {
	return {};
}
