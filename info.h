#ifndef INFO_H
#define INFO_H

class info{
private:
    double casos, obitos;
public:
    double getcasos() const{
        return casos;
    }
    double getobitos() const{
        return obitos;
    }
    info(double n_casos=0, double n_obitos=0)
        : casos{n_casos}, obitos{n_obitos} {}
    info operator+=( const info& i){
        return info(casos+=i.casos, obitos+=i.obitos); 
    }
    info operator-( const info& i){
        return info(casos-i.casos, obitos-i.obitos);
    }
    info operator/(const info& i){
        if(i.casos==0 || i.obitos==0) return info(-1,-1);
        return info(casos/i.casos, obitos/i.obitos);
    }
};

#endif