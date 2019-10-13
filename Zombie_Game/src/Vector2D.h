
#include <iostream>

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector2D
{

public:
  float x, y;


  Vector2D(){x=0;y=0;}
  Vector2D(float x, float y){this->x=x;this->y=y;}

  Vector2D& Add(const Vector2D& vec){this->x+=vec.x;}
  Vector2D& Substract(const Vector2D& vec){this->x-=vec.x;}
  Vector2D& Multiply(const Vector2D& vec){this->x*=vec.x;}
  Vector2D& Divide(const Vector2D& vec){this->x/=vec.x;}

  friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2){return v1.Add(v2);}
  friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2){return v1.Substract(v2);}
  friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2){return v1.Multiply(v2);}
  friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2){return v1.Divide(v2);}

  Vector2D& operator+=(const Vector2D& vec){return this->Add(vec);}
  Vector2D& operator-=(const Vector2D& vec){return this->Substract(vec);}
  Vector2D& operator*=(const Vector2D& vec){return this->Multiply(vec);}
  Vector2D& operator/=(const Vector2D& vec){return this->Divide(vec);}

  Vector2D& operator*(const int& i){this->x*=i;return *this;}
  Vector2D& Zero(){this->x =0; return *this;}


};


#endif //VECTOR2D_H_
