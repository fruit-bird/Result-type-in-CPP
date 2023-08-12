# Result<T, E> (Inspired by Rust's Result)

The `Result` class is a C++ template class inspired by Rust's `Result` type. It represents the outcome of an operation that can either succeed or produce an error.

This class provides a way to handle success and error cases in a more functional programming style, similar to Rust's error handling mechanisms.

## Features
- Supports chaining operations using the `and_then` and `or_else` methods
- Allows extracting the success value using the `unwrap` and `expect` methods

## Usage
### Creating a Result
```cpp
auto success = Result<int, std::string>::Ok(42);
auto failure = Result<int, std::string>::Err("Lmao");
```

### Chaining Operations
```cpp
auto double_it = [](int x) { return x * 2.0; };
auto take_it = [](const std::string& error) { return "Greed"; };

auto the_next_person = success.and_then(double_it).or_else(take_it);
```

### Extracting the Success Value
```cpp
// ik using try defeats the purpose of a Result type, okayy
try {
    int val = success.unwrap();
    auto value = failure.expect("You thought you could get away with this");
} catch (const std::exception& e) {
    std::cout << e.what() << '\n';
}
```

## What is This?
This project is created for fun (and out of boredom). Rust's Result type is a life changer
