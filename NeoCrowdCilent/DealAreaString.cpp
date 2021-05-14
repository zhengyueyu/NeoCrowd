#include <DealAreaString.h>

vector<Point2d>* DealAreaString(string area)
{
    //Step1 :把一整串area按逗号分开
    vector<string> cuts;
    int err_msg = CutString(cuts, area);

    //检查area是否有错
    if (err_msg != 0)
        return nullptr;
    if (cuts.size() % 2 != 0)
        return nullptr;
    for (int i = 0; i < cuts.size(); i++)
    {
        if (cuts[i].find(",") != cuts[i].npos)
            return nullptr;
    }

    //Step2 :将cuts转换成多个Point
    vector<Point2d>* points;
    for (unsigned i = 0; i < cuts.size(); i+=2)
    {
        float a = atof(cuts[i].c_str());
        float b = atof(cuts[i + 1].c_str());
        Point2d p = Point2d(a, b);
        points->push_back(p);
    }
    return points;
}

int CutString(vector<string>& cutted, string temp)
{
    unsigned int left = 0;
    unsigned int right = 0;
    for (; right <= temp.length(); right++)
    {
        if(temp[right] == ',' || right == temp.length())
        {
            string str(temp, left, right - left);
            cutted.push_back(str);
            left = right + 1;
        }
    }
    return 0;
}
