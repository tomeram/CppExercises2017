#include "RotatableSolution.h"

bool RotatableSolution::solve()
{
	return solve(0, 0);
}

bool RotatableSolution::solve(int i, int j)
{
	short leftFit;
	short topFit;

	if (i == 0) // First row
	{
		topFit = 0;
	}
	else
	{
		topFit = -internalGetPieceRotationContainer(i - 1, j).getBottom();
	}

	if (j == 0) // First column
	{
		leftFit = 0;
	}
	else
	{
		leftFit = -internalGetPieceRotationContainer(i, j - 1).getRight();
	}

	list<PieceRotationContainer>& optionsList = m_Pieces->getEQClass(leftFit, topFit);

	//we keep here a bool if we used a piece with [right edge + 1][bottom edge + 1].
	//top and left are dictaded from the previous calls to solve(). 
	//if we tried a type before, no need to try it again.
	bool triedRightBottomTypes[3][3] = { false, false, false, false, false, false, false, false, false };

	bool success = false;

	list<PieceRotationContainer>::iterator iter = optionsList.begin();

	//debug
	#ifdef DEBUG_SHOW_PROGRESS
	int optionListLength = (int)optionsList.size();
	int pieceTriesCounter = 0; // for debug
	#endif


	while (iter != optionsList.end()) {
		// debug
		#ifdef DEBUG_SHOW_PROGRESS
		pieceTriesCounter++; 
		#endif

		PieceRotationContainer tile = *iter;

		// go to the first unused tile
		if (tile.isUsed())
		{			
			iter++;
			continue;
		}

		// if tried this type before, skip it
		if (triedRightBottomTypes[tile.getRight() + 1][tile.getBottom() + 1])
		{
			iter++;
			continue;
		}

		triedRightBottomTypes[tile.getRight() + 1][tile.getBottom() + 1] = true;

		if (i == (m_heigt - 1)) // Last Row
		{
			if (tile.getBottom() != 0)
			{
				// tile mismatch at bottom
				iter++;
				continue;
			}
		}

		if (j == (m_width - 1))
		{
			if (tile.getRight() != 0)
			{
				// tile mismatch at right
				iter++;
				continue;
			}
		}

		tile.setUsed(true); // mark the piece as used
		internalAccessPieceRotationContainer(i, j) = tile; // copy the rotation container to the solution


		//this is for debug
		#ifdef DEBUG_SHOW_PROGRESS
		debugGetSolutionAsString(i, j, pieceTriesCounter, optionListLength);
		#endif
		// end of debug

		if ((i == (m_heigt - 1)) && (j == (m_width - 1)))
		{
			success = true;
		}
		else
		{
			int nextj = (j + 1) % m_width; // at m_width go back to 0
			int nexti = i + ((j + 1) / m_width);

			success = solve(nexti, nextj);
		}
		if (success)
		{
			// Solved everything
			return true;
		}
		else
		{
			// mark as unsolved (avoid garbage in the solution)
			internalAccessPieceRotationContainer(i, j).setUsed(false); // mark the piece as unused
			internalAccessPieceRotationContainer(i, j).SetPiece(nullptr);
			iter++;
		}
	}

	return false; // tried all options, no solution for i,j
}

#ifdef DEBUG_SHOW_PROGRESS
time_t global_last_debug_write_to_screen = time(NULL);

string RotatableSolution::debugGetSolutionAsString(int posi, int posj, int pieceTriesCounter, int optionListLength)
{

	if (m_triedSolutionCounter.size() != (unsigned int)m_heigt) //first run
	{
		m_triedSolutionCounter.resize(m_heigt);
		m_optionsCounter.resize(m_heigt);
	}

	if (m_triedSolutionCounter.at(posi).size() != (unsigned int)m_width) //first run
	{
		m_triedSolutionCounter.at(posi).resize(m_width);
		m_optionsCounter.at(posi).resize(m_width);
	}

	m_triedSolutionCounter.at(posi).at(posj) = pieceTriesCounter;
	m_optionsCounter.at(posi).at(posj) = optionListLength;

	time_t diff = time(NULL) - global_last_debug_write_to_screen; //time(nullptr)->tm_sec - global_last_debug_write_to_screen->tm_sec;
	if (diff < 2)
	{
		return "";
	}


	std::stringstream output;
	output << "trying (" << m_heigt << " x " << m_width << ") board" << endl; //debug !
	output << "pos:(" << posi << "," << posj << ") trying piece " << pieceTriesCounter << " out of " << optionListLength << endl; //debug !

	for (int i = 0; i < m_heigt; i++)
	{
		for (int j = 0; j < m_width; j++) {
			if (j > 0) {
				output << "|";
			}

			// older version - write the id. less usefull

			//const Piece* piecePtr = internalGetPiecePtr(i, j);
			//int id;
			//if (piecePtr != nullptr)
			//{
			//	id = piecePtr->getId();
			//}
			//else
			//{
			//	id = 0;
			//}
			//
			//if (id < 10)
			//{
			//	// space for single digits
			//	output << " ";
			//}

			int perc;
			if ((i*m_width + j) <= (posi*m_width + posj))
			{
				perc = (int)trunc(100 * m_triedSolutionCounter.at(i).at(j) / (float)m_optionsCounter.at(i).at(j));
			}
			else
			{
				perc = 0;
			}
			if (perc < 10)
			{
				// space for single digits
				output << " ";
			}
			if (perc < 100)
			{
				// space for double digits
				output << " ";
			}

			output /*<< std::to_string(id) << ":" */ << perc << "%";
		}

		output << std::endl;
	}


	system("CLS"); // windows clearscreen
	std::cout << output.str() << endl << std::flush;
	//update time of last write
	global_last_debug_write_to_screen = time(NULL);

	return output.str();
}
#endif
