#ifndef NODE_IMPL
#error Do not include this file directly
#endif

#include <iostream>

namespace fennecs {

template <typename Type>
Node<Type>::Node()
    : next_{this},
      prev_{this} {
}

template <typename Type>
Node<Type>::Node(Node* next, Node* prev)
    : next_{next},
      prev_{prev} {
}

template <typename Type>
Node<Type>* Node<Type>::Next() {
  ASSERT(IsValid(), "Internal assertion failure");

  return next_;
}

template <typename Type>
Node<Type>* Node<Type>::Prev() {
  ASSERT(IsValid(), "Internal assertion failure");

  return prev_;
}

template <typename Type>
Type* Node<Type>::AsContent() {
  return reinterpret_cast<Type*>(this);
}

template <typename Type>
bool Node<Type>::IsLinked() const {
  ASSERT(IsValid(), "Internal assertion failure");

  return !(prev_ == this && next_ == this);
}

template <typename Type>
void Node<Type>::LinkAfter(Node* node) {
  // std::cout << __func__ << std::endl;

  ASSERT(IsValid(), "Internal assertion failure");
  ASSERT(node != nullptr, "Node must be valid pointer");
  ASSERT(!node->IsLinked(), "Unable to link already linked node");

  next_->prev_ = node;
  node->next_ = next_;
  next_ = node;
  node->prev_ = this;
}

template <typename Type>
void Node<Type>::LinkBefore(Node* node) {
  // std::cout << __func__ << std::endl;

  ASSERT(IsValid(), "Internal assertion failure");
  ASSERT(node != nullptr, "Node must be a valid pointer");
  ASSERT(!node->IsLinked(), "Unable to link already linked node");

  prev_->next_ = node;
  node->prev_ = prev_;
  prev_ = node;
  node->next_ = this;

  ASSERT(IsValid(), "Internal assertion failure");
  ASSERT(node->IsValid(), "Internal assertion failure");
}

template <typename Type>
void Node<Type>::Unlink() {
  // std::cout << __func__ << std::endl;

  ASSERT(IsValid(), "Internal assertion failure");
  ASSERT(IsLinked(), "Unable to unlink already unlinked node");

  prev_->next_ = next_;
  next_->prev_ = prev_;
  prev_ = this;
  next_ = this;
}

template <typename Type>
bool Node<Type>::IsValid() const {
  // std::cout << next_ << std::endl;
  // std::cout << prev_ << std::endl;
  // std::cout << this << std::endl;

  return next_ != nullptr && prev_ != nullptr
      && ((prev_ == this && next_ == this) || (prev_ != this && next_ != this));
}

}  // namespace fennecs