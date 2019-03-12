#include "combofield.h"

#include "ui/comboboxex.h"

ComboField::ComboField(EffectRow* parent, const QString& id) :
  EffectField(parent, id, EFFECT_FIELD_COMBO)
{}

void ComboField::AddItem(const QString &text, const QVariant &data)
{
  ComboFieldItem item;

  item.name = text;
  item.data = data;

  items_.append(item);
}

QWidget *ComboField::CreateWidget()
{
  ComboBoxEx* cb = new ComboBoxEx();

  cb->setScrollingEnabled(false);

  for (int i=0;i<items_.size();i++) {
    cb->addItem(items_.at(i).name);
  }

  connect(cb, SIGNAL(activated(int)), this, SLOT(UpdateFromWidget(int)));
  connect(this, SIGNAL(EnabledChanged(bool)), cb, SLOT(setEnabled(bool)));

  return cb;
}

void ComboField::UpdateFromWidget(int index)
{
  SetValueAt(Now(), items_.at(index).data);
}
