/*
 * Задание (Вар. 31)
 * Движение закрашенного эллипса по 
 * треугольному контуру с изменением 
 * цвета при изменении направления движения.
 */

#include <windows.h>
#include <iostream>

#define SLEEP_DURATION 16

POINT operator-(const POINT& a, const POINT& b)
{
  return { a.x - b.x, a.y - b.y };
}

POINT operator+(const POINT& a, const POINT& b)
{
  return { a.x + b.x, a.y + b.y };
}

POINT operator*(const POINT& a, const double b)
{
  return { LONG((double)a.x * b), (LONG)((double)a.y * b) };
}

class DrawingEllipse
{
 private:
  RECT size;
  POINT center;
  POINT (*moveFunc)(time_t);

 public:
  DrawingEllipse(RECT size, POINT(*moveFunc)(time_t))
      : size(size)
      , moveFunc(moveFunc)
  {
    center = moveFunc(0);
  };

  void tick(time_t time)
  {
    center = moveFunc(time);
  }

  RECT getFrameBounds() const
  {
    return {
        size.left   + center.x,
        size.top    + center.y,
        size.right  + center.x,
        size.bottom + center.y
    };
  }
};

POINT moveFunc(time_t time)
{
  static const POINT trianglePoints[] =
      {
          {0, 0},
          {600, 0},
          {0, 600}
      };

  static const POINT deltaPoints[] =
      {
          trianglePoints[1] - trianglePoints[0],
          trianglePoints[2] - trianglePoints[1],
          trianglePoints[0] - trianglePoints[2]
      };

  time_t period = time % 1000;

  if (period < 300)
    return trianglePoints[0] + deltaPoints[0] * (period / 300.);
  else if (period < 600)
    return trianglePoints[1] + deltaPoints[1] * ((period - 300) / 300.);
  else
    return trianglePoints[2] + deltaPoints[2] * ((period - 600) / 300.);
}

COLORREF colorFunc(time_t time)
{
  // three colors loop
  time_t period = time % 1000;
  if (period < 300)
    return RGB(0xFF, 0x00, 0x00);
  else if (period < 600)
    return RGB(0x00, 0xFF, 0x00);
  else
    return RGB(0x00, 0x00, 0xFF);
}

int main()
{
  size_t width = 50, height = 50;
  std::cout << "Введите ширину и высоту эллипса: ";

  do {
    std::cin >> width >> height;
  } while (std::cin.fail());
  std::cin.ignore();
  std::cin.clear();

  auto figure = new DrawingEllipse{ {0, 0, (LONG)width, (LONG)height}, moveFunc};

  time_t time = 0;

  HWND hConsole = GetConsoleWindow();
  HDC hdc = GetDC(hConsole);
  HBRUSH hbrBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);
  HPEN hPen = CreatePen(PS_SOLID, 7, RGB(0xFF, 0xFF, 0xFF));
  SelectObject(hdc, hPen);

  for (;;)
  {
    RECT rcConsole;
    GetClientRect(hConsole, &rcConsole);
    FillRect(hdc, &rcConsole, hbrBlack);

    HBRUSH hbrFig = CreateSolidBrush(colorFunc(time));
    SelectObject(hdc, hbrFig);

    figure->tick(time);

    auto [left, top, right, bottom] = figure->getFrameBounds();
    Ellipse(hdc, left, top, right, bottom);

    time += SLEEP_DURATION;
    Sleep(SLEEP_DURATION);

    DeleteObject(hbrFig);
  }

  delete figure;
  DeleteObject(hPen);
  ReleaseDC(hConsole, hdc);

  return 0;
}