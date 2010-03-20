/**************************************************************************
*   Copyright (C) 2006-2010 by Michael Hoffer                             *
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

#include "File.h"
#include "HeaderTag.h"
#include "DoubleField.h"
#include "IntegerField.h"

#include <QDir>
#include <QStringList>

using namespace std;

class CharNetSolver : public NetSolver
{
        public:
                CharNetSolver(string directory, vector<int> layers): NetSolver()
                {

                    dataFolder = directory;

                        //vector <int> layerSize;
                        //layerSize.push_back( 30 );
                        ////layerSize.push_back( 50 );
                        //layerSize.push_back( 30 );
                        //layerSize.push_back( 20 );
                        //layerSize.push_back( 10 );

                        net.createNet( 256, 1, layers );

                        QDir trueDir(QString(directory.c_str())+QString("/true"));

                        QStringList filters;

                        filters << "*.img";

                        QStringList fileListTrue = trueDir.entryList (filters);

                        for ( int i = 0; i < fileListTrue.size(); i++ )
                        {
                            std::stringstream stream;
                            stream << dataFolder << "/true/" << fileListTrue.at(i).toStdString();

                            trueIn.push_back( new NNetInput( stream.str() ) );
                        }

                        QDir falseDir(QString(directory.c_str())+QString("/false"));
                        QStringList fileListFalse = falseDir.entryList (filters);

                        for ( int i = 0; i < fileListFalse.size(); i++ )
                        {
                            std::stringstream stream;
                            stream << dataFolder << "/false/" << fileListFalse.at(i).toStdString();

                            falseIn.push_back( new NNetInput( stream.str() ) );
                        }

                        //vector <string> letters;

                        //letters.push_back( "b" );
                        //letters.push_back( "c" );
                        //letters.push_back( "d" );
                        //letters.push_back( "e" );

                        //for ( int j = 0; j < letters.size();j++ )
                        //{
                        //        for ( int i = 1; i <= 5; i++ )
                        //        {
                        //                stringstream stream;

                        //                stream << letters[j] << "0" << i << ".img";

                        //                falseIn.push_back( new NNetInput( dataFolder + "/false/" + stream.str() ) );
                        //        }
                        //}
                }

                CharNetSolver( string fileName ): NetSolver( fileName )
                {
                        // code
                }


                virtual void fitnessFunction();

                vector<NNetInput*> trueIn;
                vector<NNetInput*> falseIn;
                string dataFolder;
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
                net.saveNet( dataFolder + "/solver.net" );
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
        if ( trueCases > 30 ) trueCases += 1000000000;
        if ( trueCases > 35 ) trueCases += 10000000000;
        if ( trueCases > 40 ) trueCases += 100000000000;



        actualEntity->setFitness( trueCases*trueCases*trueCases);

}


void usage() {
     std::cout << ">> Usage: charsolver training folder" << std::endl;
     std::cout << "          charsolver recognition netfile imgfile" << std::endl;
}

bool training(string dataFolder) {


    HeaderTag *header = new HeaderTag();
    IntegerField *populationSize = new IntegerField("population-size",1);
    IntegerField *maxIterations = new IntegerField("max-iterations",1);
    DoubleField *mutationRate = new DoubleField( "mutation-rate", 1 );
    DoubleField *crossoverRate = new DoubleField( "crossover-rate", 1 );
    IntegerField *netLayers = new IntegerField("net-layers");

    File f;

    f.addElement( header );
    f.addElement( populationSize );
    f.addElement( maxIterations );
    f.addElement( mutationRate );
    f.addElement( crossoverRate );
    f.addElement( netLayers );

    bool success = f.load(dataFolder+"/charsolver.conf");

    if (!success) {
        return false;
    }

    if (header->getFileType()!="CharSolver-File") {
        std::cerr << ">> Error: unknown file format of config file!" << std::endl;
        return false;
    }

    if (header->getVersion()!=0.1) {
        std::cerr << ">> Error: version " << header->getVersion() << " of config file not supported!" << std::endl;
        return false;
    }

    std::cout << "------------- PROBLEM -------------" << std::endl;

    std::cout << ">> population size:\t" << populationSize->element(0)->getValue() << std::endl;
    std::cout << ">> max iterations:\t" << maxIterations->element(0)->getValue() << std::endl;
    std::cout << ">> crossover rate:\t" << crossoverRate->element(0)->getValue() << std::endl;
    std::cout << ">> mutation rate:\t" << mutationRate->element(0)->getValue() << std::endl;

    stringstream stream;
    vector<int> layers;

    for (int i = 0; i < netLayers->elements().size();i++) {
        string splitChar = ", ";
        if (i == netLayers->elements().size()-1) {
            splitChar="";
        }
        stream << netLayers->element(i)->getValue() << splitChar;
        layers.push_back(netLayers->element(i)->getValue());
    }


    std::cout << ">> net leyers:\t\t" << stream.str() << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    CharNetSolver solver(dataFolder,layers);

    solver.enableRealRandom( true );

    solver.initialize( populationSize->element(0)->getValue(), -10, 10 );

    solver.setEqualCrossPoints( true );
    solver.enableCloneParents( true );

    solver.setMutationRate( mutationRate->element(0)->getValue() );
    solver.setCrossOverRate( crossoverRate->element(0)->getValue() );

    solver.startSolving( maxIterations->element(0)->getValue() );

    return true;
}


int main( int argc, char * argv[] )
{

    if (argc == 1) {
        std::cerr << ">> Error: missing arguments!" << std::endl;
        usage();
    } else if (argc == 2) {
        std::cerr << ">> Error: missing file argument!" << std::endl;
        usage();
    } else if (argc == 3) {
        if (string(argv[1])=="training") {
            std::cout << ">> Mode: training" << std::endl;
            training(argv[2]);
        } else {
            std::cerr << ">> Unknown mode: \"" << argv[1] << "\" or too many arguments!" << std::endl;
            usage();
        }
    } else if (argc==4) {
        if (string(argv[1])=="recognition") {
            std::cout << ">> Mode: recognition" << std::endl;
            NNet net( argv[2] );

            net.reset();

            NNetInput *input = new NNetInput( argv[3] );
            net.setInputs( *input );
            net.sendSignals();
            cout << "VALUE: " << net.output( 0 )->finalOutput() << endl;

        }  else {
            std::cerr << ">> Unknown mode: \"" << argv[1] << "\" or too many arguments!" << std::endl;
            usage();
        }
    } else if (argc > 4) {
        std::cerr << ">> Error: too many arguments!" << std::endl;
        usage();
    }

    return 0;
}
