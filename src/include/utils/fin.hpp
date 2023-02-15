// function behaves like golang defer

template <class F>
struct Final_action {
  explicit Final_action(F f) : act(f) {}
  ~Final_action() { act(); }
  F act;
};

template <class F>
[[nodiscard]] auto finally(F f) {
  return Final_action(f);
}
