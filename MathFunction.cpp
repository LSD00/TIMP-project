// TODO добавить сереализацию в json 
void MainCalc(int a, int b, int c) {
  double x = -10;
  double x_arr[41];
  double y_arr[41];
  for (int i = 0; i < 40; i++, x+=0.5) {
    x_arr[i] = x;
    if (x < 0) {
      y_arr[i] = a / (x*x - 1);
    }
    if (x > 0 && x < 1) {
      y_arr[i] = (1 / x) + b;
    }
    if (x > 1) {
      y_arr[i] = (c * x) / (x * x + 1);
    }
  }
}
