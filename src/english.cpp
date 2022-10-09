//
// Borrowed from "crawl"
//
#include "my_english.hpp"

bool starts_with(const std::string &s, const std::string &prefix) { return s.compare(0, prefix.size(), prefix) == 0; }

bool ends_with(const std::string &s, const std::string &suffix)
{
  if (s.length() < suffix.length())
    return false;
  return s.find(suffix, s.length() - suffix.length()) != std::string::npos;
}

int ends_with(const std::string &s, const char *const suffixes[])
{
  if (! suffixes)
    return 0;

  for (int i = 0; suffixes[ i ]; ++i)
    if (ends_with(s, suffixes[ i ]))
      return 1 + i;

  return 0;
}

static bool is_vowel(const char chr)
{
  const char low = tolower(chr);
  return low == 'a' || low == 'e' || low == 'i' || low == 'o' || low == 'u';
}

// Pluralises a monster or item name. This'll need to be updated for
// correctness whenever new monsters/items are added.
std::string pluralise(const std::string &name)
{
  std::string::size_type pos;

  if (! name.empty() && name[ name.length() - 1 ] == ')' && (pos = name.rfind(" (")) != std::string::npos) {
    return pluralise(name.substr(0, pos)) + name.substr(pos);
  }

  if (! name.empty() && name[ name.length() - 1 ] == ']' && (pos = name.rfind(" [")) != std::string::npos) {
    return pluralise(name.substr(0, pos)) + name.substr(pos);
  }

  if (ends_with(name, "us")) {
    if (ends_with(name, "lotus") || ends_with(name, "status"))
      return name + "es";
    return name.substr(0, name.length() - 2) + "i";
  } if (ends_with(name, "larva") || ends_with(name, "antenna") || ends_with(name, "hypha") ||
             ends_with(name, "noma")) {
    return name + "e";
  } if (ends_with(name, "ex")) {
    // Vortex; vortexes is legal, but the classic plural is cooler.
    return name.substr(0, name.length() - 2) + "ices";
  } else if (ends_with(name, "mosquito") || ends_with(name, "ss"))
    return name + "es";
  else if (ends_with(name, "cyclops"))
    return name.substr(0, name.length() - 1) + "es";
  else if (ends_with(name, "s"))
    return name;
  else if (ends_with(name, "y")) {
    if (name == "y")
      return "ys";
    // day -> days, boy -> boys, etc
    if (is_vowel(name[ name.length() - 2 ]))
      return name + "s";
    // jelly -> jellies
    else
      return name.substr(0, name.length() - 1) + "ies";
  } else if (ends_with(name, "fe")) {
    // knife -> knives
    return name.substr(0, name.length() - 2) + "ves";
  } else if (ends_with(name, "staff")) {
    // staff -> staves
    return name.substr(0, name.length() - 2) + "ves";
  } else if (ends_with(name, "f") && ! ends_with(name, "ff")) {
    // elf -> elves, but not hippogriff -> hippogrives.
    // TODO: if someone defines a "goblin chief", this should be revisited.
    return name.substr(0, name.length() - 1) + "ves";
  } else if (ends_with(name, "mage")) {
    // mage -> magi
    return name.substr(0, name.length() - 1) + "i";
  } else if (name == "gold" || ends_with(name, "fish") || ends_with(name, "folk")) {
    return name;
  } else if (ends_with(name, "ch") || ends_with(name, "sh") || ends_with(name, "x")) {
    // To handle cockroaches, sphinxes, and bushes.
    return name + "es";
  } else if (ends_with(name, "simulacrum") || ends_with(name, "eidolon")) {
    // simulacrum -> simulacra (correct Latin pluralisation)
    // also eidolon -> eidola (correct Greek pluralisation)
    return name.substr(0, name.length() - 2) + "a";
  } else if (ends_with(name, "djinni")) {
    // djinni -> djinn.
    return name.substr(0, name.length() - 1);
  } else if (name == "foot") {
    return "feet";
  }

  return name + "s";
}

std::string apostrophise(const std::string &name)
{
  if (name.empty())
    return name;

  if (name == "you" || name == "You")
    return name + "r";

  if (name == "it" || name == "It")
    return name + "s";

  if (name == "itself")
    return "its own";

  if (name == "himself")
    return "his own";

  if (name == "herself")
    return "her own";

  if (name == "themselves" || name == "themself")
    return "their own";

  if (name == "yourself")
    return "your own";

  // We're going with the assumption that we're finding the possessive of
  // singular nouns ending in 's' more often than that of plural nouns.
  // No matter what, we're going to get some cases wrong.

  // const char lastc = name[name.length() - 1];
  return name + /*(lastc == 's' ? "'" :*/ "'s" /*)*/;
}
