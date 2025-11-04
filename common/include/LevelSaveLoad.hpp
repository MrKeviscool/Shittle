#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <limits>

#include "SerializedData.hpp"
#include "FileStreamCommon.hpp"

//bool saveSerializedLevels(const std::string& path, const std::vector<SerializedLevelWrite>& levels);

template <typename Iter,
	typename std::enable_if<
		std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value,
		void
	>::type* = nullptr
>
bool saveSerializedLevels(const std::string& path, const Iter levelStartIter, const Iter levelEndIter);
std::pair<std::vector<SerializedLevelRead>, bool> loadSerializedLevels(const std::string& path);

namespace SaveLoadDetail {

	template <typename Iter>
	static dword_t writeAmountOfLevels(std::fstream& file, const Iter startIter, const Iter endIter, const dword_t curOffset = 0) {
		fileStream::write<word_t>(file, static_cast<word_t>(std::distance(startIter, endIter)));
		return curOffset + sizeof(word_t);
	}

	template <typename Iter>
	static dword_t writeThumbnailOffsets(std::fstream& file, const Iter startIter, const Iter endIter, dword_t curOffset) {
		curOffset += static_cast<dword_t>((std::distance(startIter, endIter) * sizeof(dword_t)) + 1);

		for (auto lev = startIter; lev != endIter; ++lev) {
			fileStream::write<dword_t>(file, curOffset);
			curOffset += getThumbSize(*lev);
		}

		return curOffset;
	}

	template <typename Iter>
	static dword_t writeLevelOffsets(std::fstream& file, Iter startIter, Iter endIter, dword_t curOffset) {
		curOffset += static_cast<dword_t>(std::distance(startIter, endIter) * sizeof(dword_t) + 1);

		for (auto lev = startIter; lev != endIter; ++lev) {
			fileStream::write<dword_t>(file, curOffset);
			curOffset += getLevelSize(*lev);
		}
		return curOffset;
	}

	template <typename Iter>
	static void writeThumbnails(std::fstream& file, const Iter startIter, const Iter endIter) {
		for (auto lev = startIter; lev != endIter; ++lev) {

			const dword_t amountOfBytesInImg = getAmountOfBytesInImage(lev->thumbnail);

			fileStream::write<byte_t>(file, static_cast<byte_t>(lev->name.size()));
			for (const auto let : lev->name)
				fileStream::write<decltype(let)>(file, let);

			writeImage(file, lev->thumbnail);
		}
	}

	template <typename Iter>
	static void writeLevels(std::fstream& file, Iter startIter, Iter endIter) {
		constexpr const size_t pegSize = sizeof(SerializedPeg);
		for (auto lev = startIter; lev != endIter; ++lev) {
			fileStream::write<word_t>(file, lev->pegs.size()); //write amount of pegs
			for (const auto& peg : lev->pegs) //write pegs
				writePeg(file, peg);
			writeImage(file, lev->background);
		}
	}
};

template <typename Iter>
bool saveSerializedLevels(const std::string& path, const Iter startIter, const Iter endIter) {
	std::fstream file(path, std::ios_base::out);

	if (!file.is_open())
		return false;

	{
		dword_t curOffset = 0;
		curOffset += SaveLoadDetail::writeAmountOfLevels(file, startIter, endIter, curOffset);
		curOffset += SaveLoadDetail::writeThumbnailOffsets(file, startIter, endIter, curOffset);
		SaveLoadDetail::writeLevelOffsets(file, startIter, endIter, curOffset);
	}
	
	SaveLoadDetail::writeThumbnails(file, startIter, endIter);
	SaveLoadDetail::writeLevels(file, startIter, endIter);

	return true;
}
