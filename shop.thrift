/**

**/

struct ProductAnswer {
    1:  i32 sensorId,
    2:  i32 preis,
    3:  i32 menge
}

struct Bill {
    1:  list<ProductAnswer> produkte;
}

service ShopRequest {

    i32 requestProduct(1:i32 sendorId, 2:i32 bestellMenge),
    ProductAnswer buyProducts(1:i32 sendorId, 2:i32 bestellMenge),
    Bill getBill(),
    void ping()
    
}

