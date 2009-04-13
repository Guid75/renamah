/*
 * Renamah
 * Copyright (C) 2009 Guillaume Denry <guillaume.denry@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
