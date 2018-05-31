#ifndef SCORECHECKING_H
#define SCORECHECKING_H
#include <fstream>

//have to be a class and not namespace because the linker is screwing up somewhere
class Score
{
public:

	static void CreateScoreFile()
	{
		std::fstream appendFile;
		appendFile.open("score.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		//file does not exist
		if (!appendFile)
		{
			appendFile.open("score.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
			appendFile.close();
		}
	}

	static void SetFileScore(int aScore)
	{
		std::fstream appendFile;
		
		appendFile.open("score.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
		appendFile.clear();
		appendFile << aScore;
		appendFile.close();
	}


	static int GetFileScore()
	{
		std::ifstream fileStream;
		fileStream.open("score.txt");
		std::stringstream strStream;
		strStream << fileStream.rdbuf();

		return std::stoi(strStream.str());
	}
};
	



#endif // !SCORECHECKING_H