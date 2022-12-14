#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "Enums/Enums.h"

class Note : public QWidget{
    Q_OBJECT
public:
    Note(QWidget *parent = nullptr);
    //void setNoteViewType(const NOTE_VIEW_TYPE type);
    //NOTE_VIEW_TYPE getNoteViewTytpe() const;
    //virtual ~Note() = default;
protected:
    unsigned recordId;
    QBoxLayout* globalLay = nullptr;
    QPushButton* modifyButton = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void modifyNoteView() = 0;
};


