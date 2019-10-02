#ifndef MARISA_KEY_H_
#define MARISA_KEY_H_

#include <cctype>
#include "marisa/base.h"

namespace marisa {

#pragma pack(push,4)
class Key {
 public:
  Key() : ptr_(NULL), length_(0), upper_(false), union_() { union_.id = 0; }

  Key(const Key &key) = default;

  Key &operator=(const Key &key) = default;

  char operator[](std::size_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    char c = ptr_[i];
    return !upper_ ? c : static_cast<char>(toupper(c));
  }

  void set_str(const char *str) {
    MARISA_DEBUG_IF(str == NULL, MARISA_NULL_ERROR);
    std::size_t length = 0;
    while (str[length] != '\0') {
      ++length;
    }
    MARISA_DEBUG_IF(length > MARISA_UINT16_MAX, MARISA_SIZE_ERROR);
    ptr_ = str;
    length_ = (UInt16)length;
  }
  void set_str(const char *ptr, std::size_t length) {
    MARISA_DEBUG_IF((ptr == NULL) && (length != 0), MARISA_NULL_ERROR);
    MARISA_DEBUG_IF(length > MARISA_UINT16_MAX, MARISA_SIZE_ERROR);
    ptr_ = ptr;
    length_ = (UInt16)length;
  }
  void set_upper(bool upper) {
    upper_ = upper;
  }
  void set_id(std::size_t id) {
    MARISA_DEBUG_IF(id > MARISA_UINT32_MAX, MARISA_SIZE_ERROR);
    union_.id = (UInt32)id;
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }
  

  const char *ptr() const {
    return ptr_;
  }
  std::size_t length() const {
    return length_;
  }
  bool upper() const {
    return upper_;
  }
  std::size_t id() const {
    return union_.id;
  }
  float weight() const {
    return union_.weight;
  }

  void clear() {
    Key().swap(*this);
  }
  void swap(Key &rhs) {
    marisa::swap(ptr_, rhs.ptr_);
    marisa::swap(length_, rhs.length_);
    marisa::swap(upper_, rhs.upper_);
    marisa::swap(union_.id, rhs.union_.id);
  }

 private:
  const char *ptr_;
  UInt16 length_;
  bool upper_;
  union Union {
    UInt32 id;
    float weight;
  } union_;
};
#pragma pack(pop)

}  // namespace marisa

#endif  // MARISA_KEY_H_
