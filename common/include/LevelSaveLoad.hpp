#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include "Level.hpp"

#include "SerializedData.hpp"
#include "FileStreamCommon.hpp"

std::pair<std::vector<SerializedLevelRead>, bool> loadSerializedLevels(const std::string& path);

namespace SaveLoadDetail {

	template <typename LevelIter>
	using PegIterator_t = typename std::iterator_traits<LevelIter>::value_type::PegIterator_t;

	dword_t getAmountOfBytesInImage(const sf::Image& image);
	void writeImage(std::fstream& file, const sf::Image& image);
	void writePeg (std::fstream& file, const SerializedPeg& peg);

	//stored as little endian with a being the significant 
	inline qword_t floatPairToQword(const float a, const float b) {
		qword_t intergralA = floatToDword(a);
		dword_t intergralB = floatToDword(b);
		return (static_cast<qword_t>(intergralA) << sizeof(float)) & intergralB;
	}

	template <typename LevelIter>
	dword_t getThumbSize(const SerializedLevelWrite<PegIterator_t<LevelIter>>& lev) {
		const dword_t bytesInImg = getAmountOfBytesInImage(lev.thumbnail);
		const dword_t sizeSpecifiers = sizeof(byte_t) + sizeof(dword_t);
		return static_cast<dword_t>(lev.name.length()) + bytesInImg + sizeSpecifiers;
	}

	template <typename LevelIter>
	dword_t getLevelSize(const SerializedLevelWrite<PegIterator_t<LevelIter>>& lev) {
		const dword_t pegBytes = static_cast<dword_t>(std::distance(lev.pegsBeginIter, lev.pegsEndIter) * sizeof(SerializedPeg));
		const dword_t bytesInImage = getAmountOfBytesInImage(lev.background);
		const dword_t sizeSpecifiers = sizeof(word_t) + sizeof(dword_t);
		return pegBytes + bytesInImage + sizeSpecifiers;
	}

	template <typename LevelIter>
	static dword_t writeAmountOfLevels(std::fstream& file, const LevelIter startIter, const LevelIter endIter, const dword_t curOffset = 0) {
		fileStream::write<word_t>(file, static_cast<word_t>(std::distance(startIter, endIter)));
		return curOffset + sizeof(word_t);
	}

	template <typename LevelIter>
	static dword_t writeThumbnailOffsets(std::fstream& file, const LevelIter startIter, const LevelIter endIter, dword_t curOffset) {
		curOffset += static_cast<dword_t>((std::distance(startIter, endIter) * sizeof(dword_t)) + 1);

		for (LevelIter lev = startIter; lev != endIter; ++lev) {
			fileStream::write<dword_t>(file, curOffset);
			curOffset += getThumbSize<LevelIter>(*lev);
		}

		return curOffset;
	}

	template <typename LevelIter>
	static dword_t writeLevelOffsets(std::fstream& file, LevelIter startIter, LevelIter endIter, dword_t curOffset) {
		curOffset += static_cast<dword_t>(std::distance(startIter, endIter) * sizeof(dword_t) + 1);

		for (LevelIter lev = startIter; lev != endIter; ++lev) {
			fileStream::write<dword_t>(file, curOffset);
			curOffset += getLevelSize<LevelIter>(*lev);
		}
		return curOffset;
	}

	template <typename LevelIter>
	static void writeThumbnails(std::fstream& file, const LevelIter startIter, const LevelIter endIter) {

		for (LevelIter lev = startIter; lev != endIter; ++lev) {
			SerializedLevelWrite<PegIterator_t<LevelIter>> serialLev = *lev;
			const dword_t amountOfBytesInImg = getAmountOfBytesInImage(serialLev.thumbnail);
			fileStream::write<byte_t>(file, static_cast<byte_t>(serialLev.name.size()));
			for (const auto let : serialLev.name)
				fileStream::write(file, let);
			writeImage(file, serialLev.thumbnail);
		}
	}

	template <typename LevelIter>
	static void writeLevels(std::fstream& file, LevelIter startIter, LevelIter endIter) {
		constexpr const size_t pegSize = sizeof(SerializedPeg);
		for (LevelIter lev = startIter; lev != endIter; ++lev) {
			SerializedLevelWrite<PegIterator_t<LevelIter>> serialLev = *lev;
			fileStream::write<word_t>(file, static_cast<word_t>(std::distance(serialLev.pegsBeginIter, serialLev.pegsEndIter))); //write amount of pegs
			for (PegIterator_t<LevelIter> peg = serialLev.pegsBeginIter; peg != serialLev.pegsEndIter; ++peg) //write pegs
				writePeg(file, *peg);
			writeImage(file, lev->background);
		}
	}
};

template <typename LevelIter,
	typename std::enable_if<
		std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<LevelIter>::iterator_category>::value
		&& std::is_convertible<typename std::iterator_traits<LevelIter>::value_type, SerializedLevelWrite<SaveLoadDetail::PegIterator_t<LevelIter>>>::value
		&& std::is_convertible<typename std::iterator_traits<SaveLoadDetail::PegIterator_t<LevelIter>>::value_type, SerializedPeg>::value,
		int
	>::type = 0
>
bool saveSerializedLevels(const std::string& path, const LevelIter startIter, const LevelIter endIter) {
	std::fstream file(path, std::ios_base::out);

	if (!file.is_open())
		return false;

	{
		dword_t curOffset = 0;
		curOffset += SaveLoadDetail::writeAmountOfLevels(file, startIter, endIter, curOffset);
		curOffset += SaveLoadDetail::writeThumbnailOffsets(file, startIter, endIter, curOffset);
		SaveLoadDetail::writeLevelOffsets(file, startIter, endIter, curOffset);
	}
	
	SaveLoadDetail::writeThumbnails<LevelIter>(file, startIter, endIter);
	SaveLoadDetail::writeLevels<LevelIter>(file, startIter, endIter);

	return true;
}
