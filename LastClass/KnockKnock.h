//KnockKnock.h

#ifndef _KNOCKKNOCK_H
#define _KNOCKKNOCK_H

class ClassDiagramForm;
class KnockKnock {
public:
	KnockKnock();
	KnockKnock(const KnockKnock& source);
	~KnockKnock();
public:
	void Knocking(ClassDiagramForm *classDiagramForm);
};

#endif // _KNOCKKNOCK_H