#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <queue>

using namespace std;

constexpr unsigned edgeLength = 1000u;

struct Rectangle
{
    unsigned calcArea() const { return width * height; }
    unsigned width;
    unsigned height;
};

Rectangle findBestRectangle(unsigned minArea)
{
    constexpr unsigned minEdgeLength = 3u;
    constexpr unsigned maxEdgeLength = edgeLength;
    Rectangle bestRectangle = {1000u, 1000u};

    for (unsigned i = minEdgeLength; i < maxEdgeLength; ++i)
    {
        for (unsigned j = minEdgeLength; j < maxEdgeLength; ++j)
        {
            Rectangle suggestion = {i, j};
            if (suggestion.calcArea() >= minArea &&
                suggestion.calcArea() < bestRectangle.calcArea())
            {
                bestRectangle = suggestion;
            }
        }
    }

    return bestRectangle;
}

template <typename T>
class Matrix2
{
public:
    Matrix2(size_t size, T initial)
        : size_(size)
        , content_(size * size, initial)
    {}

    size_t size() const { return size_; }

    T at(size_t row, size_t column) const
    {
        return content_[size_ * row + column];
    }

    void set(size_t row, size_t column)
    {
        content_[size_ * row + column] = true;
    }

private:
    size_t size_;
    vector<T> content_;
};

using Field = pair<unsigned, unsigned>;

class FieldSuggester
{
public:
    FieldSuggester(const Rectangle& t, const Matrix2<bool>& garden)
        : target_(t)
        , garden_(garden)
    {
        unsigned x = 2;
        for (unsigned i = 0; i < target_.width; ++i)
        {
            unsigned y = 2;
            for (unsigned j = 0; j < target_.height; ++j)
            {
                openFields_.push(make_pair(9, make_pair(x + i, y + j)));
            }
        }
    }

    Field suggest()
    {
        while (true)
        {
            auto top = openFields_.top();
            unsigned fieldValue = calcFieldValue(top.second);
            if (top.first != fieldValue)
            {
                openFields_.pop();
                openFields_.push(make_pair(fieldValue, top.second));
                continue;
            }
            return top.second;
        }
    }

private:
    unsigned calcFieldValue(Field f) const
    {
        unsigned fields = 0;
        for (unsigned i = f.first - 1; i <= f.first + 1; ++i)
        {
            for (unsigned j = f.second - 1; j <= f.second + 1; ++j)
            {
                if (!garden_.at(i,j))
                {
                    ++fields;
                }
            }
        }
        return fields;
    }

private:
    Rectangle target_;
    const Matrix2<bool>& garden_;
    using queueT = pair<unsigned, Field>;
    priority_queue<queueT> openFields_;
};

void communicate(Field f)
{
    cout << f.first + 1 << ' ' << f.second + 1 << '\n';
}

pair<int, Field> getResponse()
{
    int a,b;
    cin >> a >> b;
    pair<int, Field> ret;
    if (a == -1)
    {
        ret.first = -1;
        return ret;
    }
    if (a == 0)
    {
        ret.first = 0;
        return ret;
    }
    ret.first = 1;
    ret.second.first = a - 1;
    ret.second.second = b - 1;
    return ret;
}

int solve()
{
    unsigned targetArea;
    cin >> targetArea;
    Matrix2<bool> garden(edgeLength, false);
    const Rectangle targetRect = findBestRectangle(targetArea);
    FieldSuggester suggester(targetRect, garden);

    while (true)
    {
        Field nextRequest = suggester.suggest();
        communicate(nextRequest);
        pair<int, Field> response = getResponse();
        if (response.first == -1)
            return 1;
        if (response.first == 0)
            break;
        Field resultingField = response.second;

        const bool wasProcessed =
            garden.at(resultingField.first, resultingField.second);
        if (wasProcessed)
            continue;

        garden.set(resultingField.first, resultingField.second);
    }

    return 0;
}

int main()
{
    uint_fast64_t t;
    cin >> t;
    for (uint_fast64_t tNumber = 1u; tNumber < t + 1; ++tNumber)
    {
        if(solve() == -1)
            return -1;
    }
    return 0;
}
