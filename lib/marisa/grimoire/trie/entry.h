#ifndef MARISA_GRIMOIRE_TRIE_ENTRY_H_
#define MARISA_GRIMOIRE_TRIE_ENTRY_H_

#include "marisa/base.h"

namespace marisa {
namespace grimoire {
namespace trie {

#pragma pack(push,4)
class Entry {
 public:
  Entry() : ptr_(static_cast<const char *>(NULL) - 1), length_(0), upper_(false), id_(0) {}

  Entry(const Entry &entry) = default;

  Entry &operator=(const Entry &entry) = default;

  char operator[](std::size_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    char c = *(ptr_ - i);
    return !upper_ ? c : static_cast<char>(toupper(c));
  }

  void set_str(const char *ptr, std::size_t length) {
    MARISA_DEBUG_IF((ptr == NULL) && (length != 0), MARISA_NULL_ERROR);
    MARISA_DEBUG_IF(length > MARISA_UINT16_MAX, MARISA_SIZE_ERROR);
    ptr_ = ptr + length - 1;
    length_ = (UInt16)length;
  }
  void set_upper(bool upper) {
    upper_ = upper;
  }
  void set_id(std::size_t id) {
    MARISA_DEBUG_IF(id > MARISA_UINT32_MAX, MARISA_SIZE_ERROR);
    id_ = (UInt32)id;
  }

  const char *ptr() const {
    return ptr_ - length_ + 1;
  }
  std::size_t length() const {
    return length_;
  }
  bool upper() const {
    return upper_;
  }
  std::size_t id() const {
    return id_;
  }

  class StringComparer {
   public:
    bool operator()(const Entry &lhs, const Entry &rhs) const {
      for (std::size_t i = 0; i < lhs.length(); ++i) {
        if (i == rhs.length()) {
          return true;
        }
        if (lhs[i] != rhs[i]) {
          return (UInt8)lhs[i] > (UInt8)rhs[i];
        }
      }
      return lhs.length() > rhs.length();
    }
  };

  class IDComparer {
   public:
    bool operator()(const Entry &lhs, const Entry &rhs) const {
      return lhs.id_ < rhs.id_;
    }
  };

 private:
  const char *ptr_;
  UInt16 length_;
  bool upper_;
  UInt32 id_;
};
#pragma pack(pop)

}  // namespace trie
}  // namespace grimoire
}  // namespace marisa

#endif  // MARISA_GRIMOIRE_TRIE_ENTRY_H_
