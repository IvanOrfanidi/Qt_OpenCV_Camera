#!/bin/bash

function remove_ext {
	echo `echo $1 | rev | cut -f 2 -d '.' | rev`
}
function remove_path {
	echo `echo $1 | rev | cut -f 1 -d '/' | rev`
}
QTDEFINES="-DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED"

echo uic...
#uic
for i in `ls ui/*.ui`; do
	# убираем расширение .ui
	out=$(remove_ext $i)
	out=$(remove_path $out)
	out=include/ui_$out.h
	# генерируем заголовочные файлы
	uic $i -o $out
done

echo moc...
#moc
for i in `ls include/*.h`; do
	# если есть макроопределение
	MACRO=`cat $i | grep Q_OBJECT`
	if [ -n "$MACRO" ]; then
		out=$(remove_ext $i)
		out=$(remove_path $out)
		out=source/moc_$out.cpp
		moc $QTDEFINES $i -o $out
	fi
done

echo "done"
