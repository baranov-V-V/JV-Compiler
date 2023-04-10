#include "core/logger.hpp"

#include "symbol_layer_tree.hpp"
#include "scope/layers/class_scope_layer.hpp"

SymbolLayerTree::SymbolLayerTree(ScopeLayer* global) : root(new ScopeLayer("root")) {
  AddLayer(this->root, "global");
}

SymbolLayerTree::~SymbolLayerTree() {
  delete root;
}

void SymbolLayerTree::AddLayer(ScopeLayer* parent, const std::string& name) {
  parent->AddChild(new ScopeLayer(parent, name));
}

/*
void SymbolLayerTree::AddLayer(ScopeLayer* parent, ScopeLayer* class_layer) {
  //change to class layer;
  parent->AddChild(new ScopeLayer(parent, class_layer, "class"));
}
*/

void SymbolLayerTree::AddClassLayer(ScopeLayer* parent, SharedPtr<ClassType> type) {
  parent->AddChild(new ClassScopeLayer(parent, type));
}

SymbolLayerTree::Iterator SymbolLayerTree::begin() {
  return SymbolLayerTree::Iterator(root);
}

SymbolLayerTree::Iterator SymbolLayerTree::end() {
  return SymbolLayerTree::Iterator(root, root, root->GetChildNum());
}

void SymbolLayerTree::DumpTree(const std::filesystem::path& path) {
  std::filesystem::path dot_file(path);

  dot_file.replace_extension("dot");
  std::string command = "dot -Tpng " + dot_file.string() + " -o " + path.string();

  LOG_DEBUG("dot file : {}", dot_file.string());
  LOG_DEBUG("png file : {}", path.string());

  if (!dot_file.parent_path().empty()) {
    std::filesystem::create_directories(dot_file.parent_path());
  }

  fmt::ostream ostream = fmt::output_file(dot_file.c_str());
  ostream.print("digraph Ast {{\n");
  ostream.print("node [shape=\"record\", style=\"filled\"];\n");

  root->GraphVizDump(ostream);

  ostream.print("}}\n");
  ostream.close();

  LOG_INFO("graphing done with code: {}", system(command.c_str()));

  std::filesystem::remove(dot_file);
}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root) : root(root), current_parent(root), curr_idx(0) {
}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root, ScopeLayer* parent, int idx) :
  root(root), current_parent(parent), curr_idx(idx) {}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root, ScopeLayer* parent) : root(root), current_parent(root), curr_idx(0) {}


ScopeLayer* SymbolLayerTree::Iterator::operator*() const {
  return current_parent->GetChild(curr_idx);
}

ScopeLayer* SymbolLayerTree::Iterator::operator->() const {
  return current_parent->GetChild(curr_idx);
}

void SymbolLayerTree::Iterator::GoDown() {
  child_indexes[current_parent] = curr_idx;

  current_parent = current_parent->GetChild(curr_idx);

  if (!child_indexes.contains(current_parent)) {
    child_indexes.insert({current_parent, 0});
  } else {
    ++child_indexes.at(current_parent);
  }

  curr_idx = child_indexes.at(current_parent);
}

void SymbolLayerTree::Iterator::GoUp() {
  child_indexes.at(current_parent) = curr_idx;

  current_parent = current_parent->GetParent();
  curr_idx = child_indexes.at(current_parent);
}

/*
SymbolLayerTree::Iterator& SymbolLayerTree::Iterator::operator++() {
  if (curr_idx == current_parent->GetChildNum()) {
    curr_idx = child_indexes.top();
    child_indexes.pop();
    current_parent = current_parent->GetParent();
  } else {
    curr_idx++;
  }

  return *this;
}
*/
