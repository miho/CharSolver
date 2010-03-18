/**************************************************************************
*   Copyright (C) 2006 by Michael Hoffer                                  *
*   info@michaelhoffer.de                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU Library General Public License as       *
*   published by the Free Software Foundation; either version 2 of the    *
*   License, or (at your option) any later version.                       *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU Library General Public     *
*   License along with this program; if not, write to the                 *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <iostream>
#include <cmath>
#include <libnetsolver.h>
#include <libnnet.h>
#include <list>
#include <genutil.h>

using namespace std;

class CharNetSolver : public NetSolver
{
	public:
		CharNetSolver(): NetSolver()
		{
			vector <int> layerSize;
			layerSize.push_back( 30 );
			//layerSize.push_back( 50 );
                        layerSize.push_back( 30 );
			layerSize.push_back( 20 );
			layerSize.push_back( 10 );

			net.createNet( 256, 1, layerSize );


                        for ( int i = 1; i <= 12; i++ )
			{
				stringstream stream;

				stream << "a0" << i << ".img";



				trueIn.push_back( new NNetInput( "./data/true/" + stream.str() ) );
			}

			vector <string> letters;

			letters.push_back( "b" );
                        letters.push_back( "c" );
                        letters.push_back( "d" );
                        //letters.push_back( "e" );

			for ( int j = 0; j < letters.size();j++ )
			{
				for ( int i = 1; i <= 5; i++ )
				{
					stringstream stream;

					stream << letters[j] << "0" << i << ".img";

					falseIn.push_back( new NNetInput( "./data/false/" + stream.str() ) );
				}
			}



		}

		CharNetSolver( string fileName ): NetSolver( fileName )
		{
			// code
		}
		virtual void fitnessFunction();

		vector<NNetInput*> trueIn;
		vector<NNetInput*> falseIn;
};

void CharNetSolver::fitnessFunction()
{
	//bool reachedTOL = false;

	int trueCases = 0;

	for ( int i = 0; i < trueIn.size(); i++ )
	{
		net.reset();

		net.setInputs( *trueIn[i] );

		net.sendSignals();

		//cout << "OUT-TRUE: " << net.output( 0 )->finalOutput() << endl;

		if ( net.output( 0 )->finalOutput() > 1 )
		{
			trueCases++;
		}
		else
		{
			trueCases--;
		}
	}
	for ( int i = 0; i < falseIn.size(); i++ )
	{
		net.reset();

		net.setInputs( *falseIn[i] );

		net.sendSignals();

		//cout << "OUT-FALSE: " << net.output( 0 )->finalOutput() << endl;

		if ( net.output( 0 )->finalOutput() < - 1 )
		{
			trueCases++;
		}
		else
		{
			trueCases--;
		}
	}


	int maxTrueCases = trueIn.size() + falseIn.size();

	double threshold = maxTrueCases ;

	if ( trueCases > 0 )
	{
		cout << " Size: " << actualEntity->size();
		cout << " Score: " << trueCases << endl;
	}

	
	if ( trueCases >= threshold )
	{
		net.saveNet( "data/solver.net" );
		this->foundSolution();
	}

	if ( trueCases < 1 ) trueCases = 1;
	if ( trueCases > 10 ) trueCases += 100;
	if ( trueCases > 12 ) trueCases += 1000;
	if ( trueCases > 14 ) trueCases += 1000;
	if ( trueCases > 16 ) trueCases += 10000;
        if ( trueCases > 18 ) trueCases += 100000;
        if ( trueCases > 20 ) trueCases += 1000000;
        if ( trueCases > 22 ) trueCases += 1000000;
        if ( trueCases > 24 ) trueCases += 10000000;
        if ( trueCases > 25 ) trueCases += 100000000;



	actualEntity->setFitness( trueCases*trueCases*trueCases);
	
}


int main( int argc, char * argv[] )
{


	if ( argc == 1 )
	{


		CharNetSolver solver;

                std::cout << argc << std::endl;

		solver.enableRealRandom( true );

                solver.initialize( 100, -10, 10 );

		solver.setEqualCrossPoints( true );
		solver.enableCloneParents( true );
                solver.setMutationRate( 0.003 );
                solver.setCrossOverRate( 0.6 );

                solver.startSolving( 10000 );
	}
	if ( argc == 2 )
	{
		NNet net( "./data/solver.net" );

		net.reset();

		NNetInput *input = new NNetInput( argv[1] );
		net.setInputs( *input );
		net.sendSignals();
		cout << "VALUE: " << net.output( 0 )->finalOutput() << endl;
	}
	return 0;
}
