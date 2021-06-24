#ifndef INFO_H
#define INFO_H

class info{
public:
    double casos, obitos;
    info(double n_casos=0, double n_obitos=0)
        : casos{n_casos}, obitos{n_obitos} {}
    friend info operator+=(info& i1, const info& i2){
        return info(i1.casos+=i2.casos, i1.obitos+=i2.obitos); 
    }
    friend info operator-(const info& i1, const info& i2){
        return info(i1.casos-i2.casos, i1.obitos-i2.obitos);
    }
    friend info operator/(const info& i1, const info& i2){
        if(i2.casos==0 || i2.obitos==0) return info(-1,-1);
        return info(i1.casos/i2.casos, i1.obitos/i2.obitos);
    }
};

#endif