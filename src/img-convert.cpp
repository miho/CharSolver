/**************************************************************************
*   Copyright (C) 2007 by Michael Hoffer and Kenneth Aar                  *
*   info@michaelhoffer.de, kenneth@grafikern.no                           *
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

//#include <QApplication>
//#include "mainwindow.h"
#include <iostream>
#include <QImage>
#include <QColor>
using namespace std;

#include "File.h"
#include "HeaderTag.h"
#include "DoubleField.h"


/*
 * Main function.
 *
 * There is not much to say here. We initialize the app, and
 * run it. There should be no reason to change anything.
 */
int main( int argc, char *argv[] )
{
	/*----------------------------------------------------------
	 * init app
	 *--------------------------------------------------------*/

	//QApplication app( argc, argv );
	//app.setQuitOnLastWindowClosed(false);

	//MainWindow mainWindow;

	//mainWindow.show();


	//return app.exec();


	if ( argc != 3 )
	{
		cerr << ">> Error: wrong number of arguments!" << endl;
	}

	QString inFile = argv[1];
	QString outFile = argv[2];

	QImage image( inFile );

	File file;

	HeaderTag *header = new HeaderTag();

	header->setFileType( "NNet-Input-File" );
	header->setVersion( 0.1 );

	file.addElement( header );

	DoubleField *doubleField = new DoubleField( "data", image.width()*image.height() );

	file.addElement( doubleField );

	QColor color;

	int i = 0;

	for ( int y = 0; y < image.width(); y++ )
	{
		for ( int x = 0; x < image.height(); x++ )
		{
			color = image.pixel( x, y );
			doubleField->element( i )->setValue( color.red() );
			i++;
		}
	}

	file.save( outFile.toStdString() );

	return 0;
}
