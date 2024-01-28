#!/bin/bash
##########################################################################
# installer_linux.sh
# Copyright (C) 2022 Kenta Ishii
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
##########################################################################
PLUGIN_NAME='Magical8bitPlug2'
PREFIX_PATH='/usr/local'
ICON_PATH='../Resources'
ICON_NAME='icon-'
ICON_SMALL_SIZE=''
ICON_BIG_SIZE='256'
ICON_EXTENSION='png'
ICON_EXTENSION_SCALABLE=''
PLUGIN_NAME_LOWERCASE=$(echo ${PLUGIN_NAME} | tr '[:upper:]' '[:lower:]')
if [[ $@ == *'uninstall'* ]]; then
  if [[ $@ == *'standalone'* ]]; then
    echo "${PLUGIN_NAME}: Uninstalling Standalone..."
    rm ${PREFIX_PATH}/bin/${PLUGIN_NAME_LOWERCASE}
  fi
  if [[ $@ == *'icons'* ]]; then
    if [[ ${ICON_SMALL_SIZE} != '' && ${ICON_EXTENSION} != '' ]]; then
      echo "${PLUGIN_NAME}: Uninstalling ${ICON_SMALL_SIZE}x${ICON_SMALL_SIZE} .${ICON_EXTENSION} Icons..."
      rm ${PREFIX_PATH}/share/icons/hicolor/${ICON_SMALL_SIZE}x${ICON_SMALL_SIZE}/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION}
    fi
    if [[ ${ICON_BIG_SIZE} != '' && ${ICON_EXTENSION} != '' ]]; then
      echo "${PLUGIN_NAME}: Uninstalling ${ICON_BIG_SIZE}x${ICON_BIG_SIZE} .${ICON_EXTENSION} Icons..."
      rm ${PREFIX_PATH}/share/icons/hicolor/${ICON_BIG_SIZE}x${ICON_BIG_SIZE}/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION}
    fi
    if [[ ${ICON_EXTENSION_SCALABLE} != '' ]]; then
      echo "${PLUGIN_NAME}: Uninstalling Scalable .${ICON_EXTENSION_SCALABLE} Icons..."
      rm ${PREFIX_PATH}/share/icons/hicolor/scalable/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION_SCALABLE}
    fi
    echo "${PLUGIN_NAME}: Uninstalling ${PLUGIN_NAME_LOWERCASE}.desktop..."
    rm ${PREFIX_PATH}/share/applications/${PLUGIN_NAME_LOWERCASE}.desktop
  fi
  if [[ $@ == *'vst3'* ]]; then
    echo "${PLUGIN_NAME}: Uninstalling VST3 Plugin..."
    rm -r ${PREFIX_PATH}/lib/vst3/${PLUGIN_NAME_LOWERCASE}.vst3
  fi
  if [[ $@ == *'lv2'* ]]; then
    echo "${PLUGIN_NAME}: Uninstalling LV2 Plugin..."
    rm -r ${PREFIX_PATH}/lib/lv2/${PLUGIN_NAME_LOWERCASE}.lv2
  fi
else
  if [[ $@ == *'standalone'* ]]; then
    echo "${PLUGIN_NAME}: Installing Standalone..."
    cp build/${PLUGIN_NAME}_artefacts/Standalone/${PLUGIN_NAME_LOWERCASE} ${PREFIX_PATH}/bin/
  fi
  if [[ $@ == *'icons'* ]]; then
    if [[ ${ICON_SMALL_SIZE} != '' && ${ICON_EXTENSION} != '' ]]; then
      echo "${PLUGIN_NAME}: Installing ${ICON_SMALL_SIZE}x${ICON_SMALL_SIZE} .${ICON_EXTENSION} Icons..."
      cp ${ICON_PATH}/${ICON_NAME}${ICON_SMALL_SIZE}.${ICON_EXTENSION} ${PREFIX_PATH}/share/icons/hicolor/${ICON_SMALL_SIZE}x${ICON_SMALL_SIZE}/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION}
    fi
    if [[ ${ICON_BIG_SIZE} != '' && ${ICON_EXTENSION} != '' ]]; then
      echo "${PLUGIN_NAME}: Installing ${ICON_BIG_SIZE}x${ICON_BIG_SIZE} .${ICON_EXTENSION} Icons..."
      cp ${ICON_PATH}/${ICON_NAME}${ICON_BIG_SIZE}.${ICON_EXTENSION} ${PREFIX_PATH}/share/icons/hicolor/${ICON_BIG_SIZE}x${ICON_BIG_SIZE}/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION}
    fi
    if [[ ${ICON_EXTENSION_SCALABLE} != '' ]]; then
      echo "${PLUGIN_NAME}: Installing Scalable .${ICON_EXTENSION_SCALABLE} Icons..."
      cp ${ICON_PATH}/${ICON_NAME}.${ICON_EXTENSION_SCALABLE} ${PREFIX_PATH}/share/icons/hicolor/scalable/apps/${PLUGIN_NAME_LOWERCASE}.${ICON_EXTENSION_SCALABLE}
    fi
    echo "${PLUGIN_NAME}: Installing ${PLUGIN_NAME_LOWERCASE}.desktop..."
    cp ${PLUGIN_NAME_LOWERCASE}.desktop ${PREFIX_PATH}/share/applications
  fi
  if [[ $@ == *'vst3'* ]]; then
    echo "${PLUGIN_NAME}: Installing VST3 Plugin..."
    if [ ! -d "${PREFIX_PATH}/lib/vst3" ]; then
      mkdir ${PREFIX_PATH}/lib/vst3
    fi
    cp -r build/${PLUGIN_NAME}_artefacts/VST3/${PLUGIN_NAME_LOWERCASE}.vst3 ${PREFIX_PATH}/lib/vst3/
  fi
  if [[ $@ == *'lv2'* ]]; then
    echo "${PLUGIN_NAME}: Installing LV2 Plugin..."
    if [ ! -d "${PREFIX_PATH}/lib/lv2" ]; then
      mkdir ${PREFIX_PATH}/lib/lv2
    fi
    cp -r build/${PLUGIN_NAME}_artefacts/LV2/${PLUGIN_NAME_LOWERCASE}.lv2 ${PREFIX_PATH}/lib/lv2/
  fi
fi
