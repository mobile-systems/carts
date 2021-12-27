#include <iostream>

struct stock { int price; int total; };
stock stocks[] = {
    { .price = 10, .total = 10 },
    { .price = 12, .total = 7 },
    { .price = 50, .total = 90 },
    { .price = 250, .total = 1 },
    { .price = 50, .total = 9 },
    { .price = 14, .total = 6 },
};

class Item {
public:
    virtual Item* prepare(int country) = 0;
    virtual int deliver() = 0;
};

class Stocked : public Item {
public:
    explicit Stocked(stock* s) : stk(s) {};
    Item* prepare(int country) override {
        return this;
    }
    int deliver() override {
        this->stk->total--;
        return this->stk->price;
    }
private:
    stock* stk;
};

class Digital : public Stocked {
public:
    explicit Digital(Stocked* s) : Stocked(*s) {};
    int deliver() override {
        return Stocked::deliver() / 2;
    }
};

class Tangible : public Stocked {
public:
    explicit Tangible(Stocked* s) : Tangible(s, 0) {};
    Item* prepare(int country) override {
        if (country == 7) {
            return new Tangible(this, 25);
        }
        return new Tangible(*this);
    }
    int deliver() override {
        return Stocked::deliver() * (1 - this->discount / 100);
    }
private:
    Tangible(Stocked* s, int d) : Stocked(*s), discount(d) {};
    int discount;
};

class Cart {
public:
    virtual Cart* add(Item* i) = 0;
    virtual Cart* recalc(int country) = 0;
    virtual int deliver() = 0;
};

class FullCart : public Cart {
public:
    FullCart(Cart* c, Item* i) : before(c), item(i) {};
    Cart* add(Item* i) override {
        return new FullCart(this, i);
    }
    Cart* recalc(int country) override {
        return new FullCart(
            this->before->recalc(country),
            this->item->prepare(country)
        );
    }
    int deliver() override {
        return this->before->deliver() + this->item->deliver();
    }
private:
    Cart* before;
    Item* item;
};

class EmptyCart : public Cart {
    Cart* add(Item* i) override {
        return new FullCart(this, i);
    }
    Cart* recalc(int country) override {
        return this;
    }
    int deliver() override {
        return 0;
    }
};

int main() {
    int max = sizeof(stocks) / sizeof(stocks[0]);
    Cart* cart = new EmptyCart();
    for (int i = 0; i < max / 2; ++i) {
        Item* item = new Digital(new Stocked(&stocks[i]));
        cart = cart->add(item);
    }
    for (int i = max / 2; i < max; ++i) {
        Item* item = new Tangible(new Stocked(&stocks[i]));
        cart = cart->add(item);
    }
    cart = cart->recalc(7);
    int total = cart->deliver();
    std::cout << "Total: " << total << "\n";
}
