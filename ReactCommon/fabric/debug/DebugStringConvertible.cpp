/**
 * Copyright (c) 2015-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "DebugStringConvertible.h"

namespace facebook {
namespace react {

std::string DebugStringConvertible::getDebugChildrenDescription(DebugStringConvertibleOptions options, int depth) const {
  if (depth >= options.maximumDepth) {
    return "";
  }

  std::string childrenString = "";

  for (auto child : getDebugChildren()) {
    childrenString += child->getDebugDescription(options, depth + 1);
  }

  return childrenString;
}

std::string DebugStringConvertible::getDebugPropsDescription(DebugStringConvertibleOptions options, int depth) const {
  if (depth >= options.maximumDepth) {
    return "";
  }

  std::string propsString = "";

  for (auto prop : getDebugProps()) {
    auto name = prop->getDebugName();
    auto value = prop->getDebugValue();
    auto children = prop->getDebugPropsDescription(options, depth + 1);
    auto valueAndChildren = value + (children.empty() ? "" : "(" + children + ")");
    propsString += " " + name + (valueAndChildren.empty() ? "" : "=" + valueAndChildren);
  }

  if (!propsString.empty()) {
    // Removing leading space character.
    propsString.erase(propsString.begin());
  }

  return propsString;
}

std::string DebugStringConvertible::getDebugDescription(DebugStringConvertibleOptions options, int depth) const {
  std::string nameString = getDebugName();
  std::string valueString = getDebugValue();
  std::string childrenString = getDebugChildrenDescription(options, depth + 1);
  std::string propsString = getDebugPropsDescription(options, depth /* The first-level props are considered as same-depth things. */);

  std::string leading = options.format ? std::string(depth, '\t') : "";
  std::string trailing = options.format ? "\n" : "";

  return leading + "<" + nameString +
    (valueString.empty() ? "" : "=" + valueString) +
    (propsString.empty() ? "" : " " + propsString) +
    (childrenString.empty() ? "/>" + trailing : ">" + trailing + childrenString + leading + "</" + nameString + ">" + trailing);
}

std::string DebugStringConvertible::getDebugName() const {
  return "Node";
}

std::string DebugStringConvertible::getDebugValue() const {
  return "";
}

SharedDebugStringConvertibleList DebugStringConvertible::getDebugChildren() const {
  return SharedDebugStringConvertibleList();
}

SharedDebugStringConvertibleList DebugStringConvertible::getDebugProps() const {
  return SharedDebugStringConvertibleList();
}

} // namespace react
} // namespace facebook
