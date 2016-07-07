/* SO 13484943 */
/* Code by http://stackoverflow.com/users/2691606/megajixiang */

#ifndef HEAPJ_H_INCLUDED
#define HEAPJ_H_INCLUDED

#include <vector>
#include <string>

static const int g_TerminationNodeValue = -999;

class HeapJ
{
public:
    HeapJ(int *pHeapArray, int numElements);
    void Print();

private:
    int *m_pHeapPointer;
    int m_numElements;
    int m_treeHeight;
    std::vector<std::string> m_printVec;
    int GetTreeHeight(int index);
    void DoPrintHeap(int index, size_t recursionLevel, int numIndents);
};


#endif /* HEAPJ_H_INCLUDED */

/* Class implementation */

//#include "HeapJ.h"
#include <iostream>

HeapJ::HeapJ(int *pHeapArray, int numElements)
{
    m_pHeapPointer = pHeapArray;
    m_numElements = numElements;
    m_treeHeight = GetTreeHeight(1);
}

void HeapJ::Print()
{
    m_printVec.clear();

    int initialIndex = 0;
    for (int i = 1; i < m_treeHeight; ++i)
    {
        int powerOfTwo = 1;
        for (int j = 0; j < i; ++j)
        {
            powerOfTwo *= 2;
        }

        initialIndex += powerOfTwo - (i-1);
    }

    DoPrintHeap(1, 0, initialIndex);

    for (size_t i = 0; i < m_printVec.size(); ++i)
    {
        std::cout << m_printVec[i] << '\n' << '\n';
    }
}

int HeapJ::GetTreeHeight(int index)
{
    const int value = m_pHeapPointer[index-1];

    if (value == g_TerminationNodeValue)
    {
        return -1;
    }

    const int childIndexLeft = 2*index;
    const int childIndexRight = childIndexLeft+1;

    int valLeft = 0;
    int valRight = 0;

    if (childIndexLeft <= m_numElements)
    {
        valLeft = GetTreeHeight(childIndexLeft);
    }

    if (childIndexRight <= m_numElements)
    {
        valRight = GetTreeHeight(childIndexRight);
    }

    return std::max(valLeft, valRight)+1;
}

void HeapJ::DoPrintHeap(int index, size_t recursionLevel, int numIndents)
{
    const int value = m_pHeapPointer[index-1];

    if (value == g_TerminationNodeValue)
    {
        return;
    }

    if (m_printVec.size() == recursionLevel)
    {
        m_printVec.push_back(std::string(""));
    }

    const int numLoops = numIndents - (int)m_printVec[recursionLevel].size();
    for (int i = 0; i < numLoops; ++i)
    {
        m_printVec[recursionLevel].append(" ");
    }

    m_printVec[recursionLevel].append(std::to_string(value));

    const int childIndexLeft = 2*index;
    const int childIndexRight = childIndexLeft+1;
    const int exponent = m_treeHeight-(recursionLevel+1);
    int twoToPower = 1;
    for (int i = 0; i < exponent; ++i)
    {
        twoToPower *= 2;
    }
    const int recursionAdjust = twoToPower-(exponent-1);

    if (childIndexLeft <= m_numElements)
    {
        DoPrintHeap(childIndexLeft, recursionLevel+1, numIndents-recursionAdjust);
    }

    if (childIndexRight <= m_numElements)
    {
        DoPrintHeap(childIndexRight, recursionLevel+1, numIndents+recursionAdjust);
    }
}

/* End Class */

const int g_heapArraySample_Size = 14;
int g_heapArraySample[g_heapArraySample_Size] =
{
    16, 14, 10, 8, 7, 9, 3, 2, 422, 101, 202,
    g_TerminationNodeValue, g_TerminationNodeValue, 0
};

int main()
{
    HeapJ myHeap(g_heapArraySample, g_heapArraySample_Size);
    myHeap.Print();

    return 0;
}

