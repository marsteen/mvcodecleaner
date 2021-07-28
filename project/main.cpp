//***************************************************************************
//
//
// @PROJECT  :    mvcodecleaner
// @VERSION  :    1.0
// @FILENAME :    main.cpp
// @DATE     :    28.07.2021
//
// @AUTHOR   :    Martin Steen
// @EMAIL    :    martin.steen@ksti.de
//
//
//***************************************************************************

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------

static bool readLine(std::ifstream& fs, string& line)
{
    char ch;
    bool EndLine = false;

    line.clear();
    do
    {
        fs.get(ch);
        if (!fs.eof())
        {
            if (ch != 0x0D)
            {
                if (ch != 0x0A)
                {
                    line.push_back(ch);
                }
                else
                {
                    // Unix lineend (0A)
                    EndLine = true;
                }
            }
            else
            {
                // Windows lineend (0D0A)
                fs.get(ch);
                EndLine = true;
            }
        }
        else
        {
            EndLine = true;
        }
    }
    while (!EndLine);

    return (line.size() > 0) || (!fs.eof());
}


//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------

static bool readFile(const std::string& filename, std::vector<std::string>& outVec, int& changed)
{
    ifstream infile(filename, ios::binary);

    bool r = false;
    changed = 0;

    if (infile.good())
    {
        std::string line;
        while (readLine(infile, line))
        {
            int lastChar = -1;
            std::string outString;
            for (int i = line.size()-1; i >= 0; i--)
            {
                if ((line[i] == ' ') || (line[i] == '\t'))
                {
                    changed++;
                    lastChar = i;
                }
                else
                {
                    break;
                }
            }
            if (lastChar >= 0)
            {
                outString = line.substr(0, lastChar);
            }
            else
            {
                outString = line;
            }
            outVec.push_back(outString);
        }
        infile.close();
        r = true;
    }
    return r;
}

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------

static bool writeFile(const std::string& filename, const std::vector<std::string>& outVec)
{
    bool r = false;

    ofstream outfile(filename);
    if (outfile.good())
    {
        for (auto it = outVec.begin(); it != outVec.end(); ++it)
        {
            outfile << *it << endl;
        }
        outfile.close();
        r = true;
    }
    return r;
}

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        std::vector<std::string> outVec;
        int changed = 0;

        if (readFile(argv[1], outVec, changed))
        {
            cout << "mvcodecleaner: readFile " << argv[1] << " ok" << endl;
            cout << "removed spaces:" << changed << endl;
            if (changed > 0)
            {
                writeFile(argv[1], outVec);
            }
        }
    }
    else
    {
        cout << "usage: mvcodecleaner <filename>" << endl;
        cout << "version 1.0" << endl;
    }
    
    return 0;
}
