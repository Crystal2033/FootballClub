#include <QWidget>
#include "Enums/Enums.h"
#include "InfoNotes/DataWidgets/calendar.h"
#include "InfoNotes/DataWidgets/combobox.h"
#include "InfoNotes/DataWidgets/datetext.h"
#include "InfoNotes/DataWidgets/label.h"
#include "InfoNotes/DataWidgets/lineedit.h"
#include "InfoNotes/DataWidgets/textfield.h"

class Note : public QWidget{
    Q_OBJECT
public:
    Note(QWidget *parent = nullptr);
    void setNoteViewType(const NOTE_VIEW_TYPE type);
    NOTE_VIEW_TYPE getNoteViewTytpe() const;
    virtual ~Note() = default;
protected:
    unsigned recordId;
    QPushButton* modifyButton = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void modifyNoteView() = 0;
};

inline Note::Note(QWidget *parent)
    :QWidget(parent)
{

}

inline void Note::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    noteViewType = type;
}

inline NOTE_VIEW_TYPE Note::getNoteViewTytpe() const
{
    return noteViewType;
}
