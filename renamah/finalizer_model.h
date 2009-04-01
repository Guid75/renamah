#ifndef FINALIZER_MODEL_H
#define FINALIZER_MODEL_H

#include "modifier_model.h"

class FinalizerModel : public ModifierModel
{
	Q_OBJECT

public:
	static FinalizerModel &instance();

	/*! Apply finalizers on the file in argument */
	void apply(const QString &fileName) const;

private:
	FinalizerModel();

	static FinalizerModel *_instance;
};

#endif
