#include <QWidget>

class Note : public QWidget{
    Q_OBJECT
public:
    Note(QWidget *parent = nullptr);
    virtual ~Note() = default;
protected:
    virtual void extend() = 0;
};

inline Note::Note(QWidget *parent)
    :QWidget(parent)
{

}
