
class Void {
private:
    Void();
};

Void::Void() {
    throw; // cannot be instantiated
}
