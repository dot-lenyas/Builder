#include <iostream>
#include <vector>


using namespace std;

enum FILLING
{
    NONE,
    CHOCOLATE,
    CREAM,
    MILKY
};

enum DOUGH
{
    D_NONE,
    LOOSE,
    PUFFED,
    SWEET
};

enum STORAGE
{
    S_NONE,
    POCKET,
    NAPKIN,
};




class BasePie {
    FILLING filling;
public:
    BasePie(FILLING filling) : filling(filling) {
    }

    string toString()
    {
        switch (filling) {
            case FILLING::CHOCOLATE: return "CHOCOLATE";
            case FILLING::CREAM: return "CREAM";
            case FILLING::MILKY: return "MILKY";
        }

        throw std::logic_error("err");
    }
};

class Pie {
    vector<BasePie *> items;
    DOUGH dough;
    STORAGE storage;

    friend class MajorCostPie;
    friend class LowCostPie;

public:
    string toString()
    {
        string s = "";

        switch (storage) {
            case STORAGE::POCKET: s += "POCKET"; break;
            case STORAGE::NAPKIN: s += "NAPKIN"; break;
        }

        for (auto & item : items) {
            s += ", " + item->toString();
        }

        switch (dough) {
            case DOUGH::LOOSE: s += ", LOOSE"; break;
            case DOUGH::PUFFED: s += ", PUFFED"; break;
            case DOUGH::SWEET: s += ", SWEET"; break;
        }

        return s;
    }
};

class PieBuilder {
protected:
    vector<FILLING> filling;
    DOUGH dough;

public:
    void addFilling(FILLING fillings) {
        filling.push_back(fillings);
    }

    void setDough(DOUGH dough) {
        this->dough = dough;
    }

    virtual Pie* build() = 0;
};

class MajorCostPie: public PieBuilder {
public:
    virtual Pie* build() {
        Pie* NewPie= new Pie();
        for (auto & f : filling) {
            NewPie->items.push_back(new BasePie(f));
        }
        NewPie->dough = dough;
        NewPie->storage = STORAGE::NAPKIN;
        return NewPie;
    }
};

class LowCostPie: public PieBuilder {
public:
    virtual Pie* build() {
        Pie* NewPie = new Pie();
        NewPie->dough = DOUGH::PUFFED;
        NewPie->storage = STORAGE::POCKET;
        return NewPie;
    }
};

void userGUI(PieBuilder &builder) {
    builder.addFilling(FILLING::MILKY);
    builder.setDough(DOUGH::SWEET);
    builder.addFilling(FILLING::CREAM);

    Pie *NewPie = builder.build();

    cout << "It's pie: " << NewPie->toString() << endl;
}