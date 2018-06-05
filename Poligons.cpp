#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct Point //Punkta struktura
{
    float x, y;

    void createPoint(float _x, float _y)
    {
        x = _x;
        y = _y;
    }


    void printP()
    {
        cout << "(" << x << ", " << y <<")" << endl;
    }
};


struct Line{ //Linijas struktura, ertibas labad liniju deklarejot taa uzreiz ir saakot no mazaakaa punkta uz lielaako.
	float ax, ay, bx, by;
	float koef, base;

	void createLine(float _ax, float _ay, float _bx, float _by)
	{
	    if (_ax > _bx)
	    {
	        ax = _bx;
	        ay = _by;
	        bx = _ax;
	        by = _ay;
	    }
	    else
	    {
	        ax = _ax;
		    ay = _ay;
		    bx = _bx;
		    by = _by;
	    }
		koef =  (by-ay) / (bx-ax);
		base = ((0-ax) * koef) + ay;
	}

	void printL ()
	{
	    cout << "Linijas funkcija: " << koef << "x:: " << base << endl;
	}
};

bool hasXPoint;

bool cmpf(float A, float B, float epsilon = 0.005f) //Funkcija kas nodrosina skaitlu ar peldoso komatu saliidzinasanu..
{
    return (fabs(A - B) < epsilon);
}

Point XPoint (Line a, Line b)
{
    hasXPoint = false;
    float xPoint;
    Point result;
	if (cmpf(a.koef,b.koef))
	{
		cout << "Paralelas linijas, pagaidaam nezinu kaa taas apstraadaat...." << endl;
	} else
	{   //Ja koeficienti nav vienaadi, un liniju krustpunkts atrodas starp nogrieznu galiem, tad nogriezni krustojas
		xPoint =  (b.base - a.base) /  (a.koef - b.koef);
		if ((xPoint >= b.ax && xPoint <= b.bx) && (xPoint >= b.ax && xPoint <= b.bx))
		{
		    result.createPoint(xPoint, a.base + (a.koef * xPoint));
		    hasXPoint = true;
		}
	}
	return result;
};
//Globaalie mainiigie, ar meerki nedubleet datus atkaartoti izsaucot funkcijas, kuraam tie buutu nepieciesami
int N, xpointCount;
Line lines[1000];
Point point[1000];
Point p0;
int result_index = 0;
int resultlineindex[1000];
int resultpointindex[1000];
int resultcount = 0;

int lineExsist(Point a, Point b) //Funkcija kas paarbauda vai konkreetiem diviem punktiem var atrast nogriezni, kas tos savieno
{
    Line line;
    line.createLine(a.x,a.y,b.x,b.y);
    for (int i = 0; i < N; i++)
    {
        if (cmpf(line.koef,lines[i].koef) && cmpf(line.base,lines[i].base) && line.ax >= lines[i].ax && line.bx <= lines[i].bx)
        {
            return i;
        };
    }
    return -1;
}

// funkcija, kas nodrosina divu punktu apmaiņu masiivaa
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

//Funkcija, kas atgriez attaaluma starp diviem punktiem kvadratisko vertibu
double SqrDist(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

/*
Funkcija, kas nosaka secigu punktu novietojumu, iespejamas vertibas:
0: punkti atrodas uz vienas taisnes
1: punkti ir novietoti pulkstenraditaja virziena
2: punkti izvietoti preteji pulkstenraditaja virzienam
*/
int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (cmpf(0,val)) return 0;
    return (val > 0)? 1: 2;
}

//Funkcija, kas saliidzina punktus attieciba pret bazes punktu, tiek izmantota pie punktu kaartosanas.
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (SqrDist(p0, *p2) >= SqrDist(p0, *p1))? -1 : 1; //Jan punti ir uz vienas taisnes par pirmo nemam tuvaako punktu.

   return (o == 2)? -1: 1;
}

void forceSort(int start, int size, Point newCenter)
{
    p0 = newCenter;
    qsort(&point[start], size-start, sizeof(Point), compare);
}



/*
Galvena aprekina funkcija.
Vispirms sakartojam liniju krustpunktus, lai vareetu atrast pec iespejas lielaaku daudzsturi.
Ejam cauri visiem punktiem, kameer atrodam punktu, stap kuru un sakumpunktu eksistee nogrieznis.
Punktu, ar kuru var veidot konturu liekam aiz sakumpunkta un atkartoti sakartojam punktus, bet soreiz par pamatpunktu nemam jau atrasto punktu.
Rekursivi izsaucam funkciju, kamer no dotajiem punktiem tiek atrasts noslegts konturs.
Peec rekursijas cikla piefikejam visus punktus un nogrieznus, kas veido noslegtu konturu.
*/
int recHull(int startIndex = 0)
{
    Point p1 = point[startIndex];
    Point p2;
    startIndex++;
    qsort(&point[startIndex], xpointCount-startIndex, sizeof(Point), compare);
    int lineIndex = -1;
    int resultLineIndex = -2;
    for (int i = startIndex; i < xpointCount; i++)
    {
        lineIndex = lineExsist(p1,point[i]);
        if (lineIndex >= 0)
        {
            swap(point[i], point[startIndex]);
            p0 = point[startIndex];
            qsort(&point[startIndex], xpointCount-startIndex, sizeof(Point), compare);
            resultLineIndex = recHull(startIndex);
            if (resultLineIndex >= 0 )
            {
                p2 = point[i];
                break;
            }
        }
   }
   if (resultLineIndex == -2) //Nosledzosais punkts, nevar atrast sasaisti ar atlikusajiem punktiem, tapec veicam parbaudi uz sakumpunktu
   {
       resultLineIndex = lineExsist(p1,point[result_index]);
       if (resultLineIndex >= 0 )
       {
           resultlineindex[resultcount] = resultLineIndex;
           resultpointindex[resultcount++] = startIndex-1;
           result_index = startIndex-1;
       }
       return -1;
    }

   if (resultLineIndex == -1)
   {
       resultLineIndex = lineExsist(p1,point[result_index]);
       if (resultLineIndex >= 0 )
       {
           resultlineindex[resultcount] = resultLineIndex;
           resultpointindex[resultcount++] = startIndex-1;
       }
       return lineIndex;
   }
    resultlineindex[resultcount] = lineIndex;
    resultpointindex[resultcount++] = startIndex-1;
   return lineIndex;
}
int main()
{
    float ax, ay, bx, by;
    /*cin >> N;

    //Lîniju nolasîðana;
    for (int i = 0; i < N; i++)
	{
		cin >> ax >> ay >> bx >> by;
        lines[i].createLine(ax,ay,bx,by);
	}*/

	N = 20;
	lines[0].createLine(-2763,1007,-1120,1656);
	lines[1].createLine(-1215,2534,1092,2445);
	lines[2].createLine(1597,1108,2182,157);
	lines[3].createLine(-1483,1870,-482,820);
	lines[4].createLine(648,-70,2835,-189);
	lines[5].createLine(-482,820,-443,-932);
	lines[6].createLine(1092,2445,2201,2811);
	lines[7].createLine(-1215,2534,-4058,2821);
	lines[8].createLine(-2763,1007,-2632,-209);
	lines[9].createLine(-1017,-2260,-700,-1735);
	lines[10].createLine(-3811,-179,-3018,-873);
	lines[11].createLine(3469,2385,3638,1642);
	lines[12].createLine(641,3371,605,1621);
	lines[13].createLine(1141,-3483,1998,-1912);
	lines[14].createLine(-157,-447,-1808,-2049);
	lines[15].createLine(-3405,3332,-3898,1766);
	lines[16].createLine(2674,934,2942,1879);
	lines[17].createLine(-1345,-1971,-3038,-405);
	lines[18].createLine(-2995,-645,-2431,468);
	lines[19].createLine(1164,412,1221,-659);

	//ja divas linijas krustojas atzimejam punktu un taisnu indeksus kuras taja krustojas



	xpointCount = 0; // Meklejam visus nogrieznu krustpunktus.
	for (int i = 0; i < N-1; i++)
	{
	    for (int j = i+1; j < N; j++)
	    {
	        point[xpointCount] = XPoint(lines[i], lines[j]);
	        if (hasXPoint)
            {
                xpointCount++;
            }
	    }
	}

    float ymin = point[0].y;
    int min = 0;
    for (int i = 1; i < xpointCount; i++)
    {
        float y = point[i].y;
        if ((y < ymin) || (ymin == y &&
             point[i].x < point[min].x))
        ymin = point[i].y, min = i;
    }

    swap(point[0], point[min]);

    p0 = point[0];
    recHull();
	for (int i=0; i<resultcount; i++)
    {
        if (i+1 < resultcount && resultlineindex[i] != resultlineindex[i+1])
            cout << resultlineindex[i] << ":", lines[resultlineindex[i]].printL(), point[resultpointindex[i]].printP();
    }
    cout << resultlineindex[resultcount-1] << ":", lines[resultlineindex[resultcount-1]].printL(), point[resultpointindex[resultcount-1]].printP();
    return 0;
}
