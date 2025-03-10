/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2021 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <list>
#include <QString>
#include <vector>

#include "common/define.h"

namespace olive {

class Project;

class UndoCommand
{
public:
  UndoCommand();

  virtual ~UndoCommand(){}

  DISABLE_COPY_MOVE(UndoCommand)

  bool has_prepared() const {return prepared_;}
  void set_prepared(bool e) {prepared_ = true;}

  void redo_now();
  void undo_now();

  void redo_and_set_modified();
  void undo_and_set_modified();

  virtual Project* GetRelevantProject() const = 0;

  const QString& name() const
  {
    return name_;
  }

  void set_name(const QString& name)
  {
    name_ = name;
  }

protected:
  virtual void prepare(){}
  virtual void redo() = 0;
  virtual void undo() = 0;

private:
  bool modified_;

  QString name_;

  Project* project_;

  bool prepared_;

};

class MultiUndoCommand : public UndoCommand
{
public:
  MultiUndoCommand();

  virtual Project* GetRelevantProject() const override
  {
    return nullptr;
  }

  void add_child(UndoCommand* command)
  {
    children_.push_back(command);
  }

  int child_count() const
  {
    return children_.size();
  }

  UndoCommand* child(int i) const
  {
    return children_[i];
  }

protected:
  virtual void redo() override;
  virtual void undo() override;

private:
  std::vector<UndoCommand*> children_;

  bool done_;

};

}

#endif // UNDOCOMMAND_H
