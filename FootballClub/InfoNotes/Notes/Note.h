#include <QWidget>
#include "Enums/Enums.h"

class Note : public QWidget{
    Q_OBJECT
public:
    Note(QWidget *parent = nullptr);
    void setNoteViewType(const NOTE_VIEW_TYPE type);
    NOTE_VIEW_TYPE getNoteViewTytpe() const;
    virtual ~Note() = default;
protected:
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
