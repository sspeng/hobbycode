/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is XSmilAgent
 *
 * The Initial Developer of the Original Code is
 * ITC-irst, TCC Division (http://tcc.fbk.eu) Trento / ITALY.
 * Portions created by the Initial Developer are Copyright (C) 2004 - 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * - Koray Balci (koraybalci@gmail.com)
 * ***** END LICENSE BLOCK ***** */
/*! 
	\file		ItalianFlite.h
	\brief		Italian flite hook.
*/

#pragma once
#include "ITTSEngine.h"
#include "TTSEngineMaker.h"

/*!
	\brief Italian flite hook.
	\author Koray Balci

	Handles speech synthesis using Italian flite as TTS engine.
*/
class ItalianFlite :
	public ITTSEngine
{
	std::string m_pathname;
	void createSmilVisitor();
public:
	std::map<std::string, float> speak(const std::string& speech, const std::string& filename);
	ItalianFlite(const std::string& pathname);
};

/*!
	\brief Maker class for ItalianFlite class.
	\author Koray Balci
	
	Pluggable factory pattern maker class for ItalianFlite. 
*/
class ItalianFliteMaker : public TTSEngineMaker
{
private:
	ItalianFliteMaker() : TTSEngineMaker("it_flite"){}
	ITTSEngine* makeTTSEngine(const std::string& pathname, const std::string& unusedini) const
	{
		return new ItalianFlite(pathname);
	}
	static const ItalianFliteMaker m_regItalianFlite;
};
