extern int baz();
extern int bar(int);

void foo(int a, int b) {
  int var = a + b;
  if (var == 0xFF) {
    bar(var);
    var = baz();
  }
  bar(var);
}
