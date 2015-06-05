#ifndef __COMMON_SERVER_OPT_H_
#define __COMMON_SERVER_OPT_H_

/*
 *
 *	Detail: ���÷���������
 *   
 * Copyright (c) Created by hzd 2015-5-19.All rights reserved
 *
 */

#include "BaseDefine.h"
#include "BaseSingle.h"
#include "CommonDefine.h"
#include <string>

struct ServerInfoOpt
{
	int32 nID;			// ��������ַ 
	string strHost;		// �������˿� 
	int32 nPort;		// ���������� 
	int32 nType;		// ������ID 

};

struct DatabaseInfoOpt
{
	string strHost;    // ���ݿ��ַ
	int32 nPort;	   // �û���
	string strUser;	   // ����
	string strPass;	   // ���ݿ���
	string strDbname;  // �˿�
};

class NetServerOpt : public BaseSingle<NetServerOpt>
{
public:

	bool LoadServerConfig(string cPath,EServerType eServerType)
	{

		using namespace boost::property_tree;
		ptree cPtreeDoc;
		ptree cPtreeDocItems;
		ptree cLocalInfo;
		ptree cRemoteInfo;
		ptree cClientInfo;
		ptree cDatabaseInfo;

		m_eServerType = eServerType;

		read_xml(cPath, cPtreeDoc, boost::property_tree::xml_parser::trim_whitespace);
		cPtreeDocItems = cPtreeDoc.get_child("items");

#define XMLATTR(KEY) "<xmlattr>."#KEY 

		cRemoteInfo = cPtreeDocItems.get_child("remote");
		m_sRemoteInfo.nID = cRemoteInfo.get<uint32>(XMLATTR(id));
		m_sRemoteInfo.strHost = cRemoteInfo.get<string>(XMLATTR(host));
		m_sRemoteInfo.nPort = cRemoteInfo.get<uint32>(XMLATTR(port));
		m_sRemoteInfo.nType = cRemoteInfo.get<uint32>(XMLATTR(type));

		cLocalInfo = cPtreeDocItems.get_child("local");
		m_sLocalInfo.nID = cLocalInfo.get<uint32>(XMLATTR(id));
		m_sLocalInfo.strHost = cLocalInfo.get<string>(XMLATTR(host));
		m_sLocalInfo.nPort = cLocalInfo.get<uint32>(XMLATTR(port));
		m_sLocalInfo.nType = cLocalInfo.get<uint32>(XMLATTR(type));

		if(eServerType == ESERVER_TYPE_DP)
		{
			cDatabaseInfo = cPtreeDocItems.get_child("database");
			m_sDbInfo.strHost = cDatabaseInfo.get<string>(XMLATTR(host));
			m_sDbInfo.strUser = cDatabaseInfo.get<string>(XMLATTR(user));
			m_sDbInfo.strPass = cDatabaseInfo.get<string>(XMLATTR(pass));
			m_sDbInfo.strDbname = cDatabaseInfo.get<string>(XMLATTR(dbname));
		}

		if(eServerType == ESERVER_TYPE_FEP)
		{
			cClientInfo = cPtreeDocItems.get_child("client");
			m_sClientInfo.nID = cClientInfo.get<uint32>(XMLATTR(id));
			m_sClientInfo.strHost = cClientInfo.get<string>(XMLATTR(host));
			m_sClientInfo.nPort = cClientInfo.get<uint32>(XMLATTR(port));
			m_sClientInfo.nType = cClientInfo.get<uint32>(XMLATTR(type));
		}

#undef XMLATTR

		return true;
	}

	ServerInfoOpt& GetLocalServerInfo()
	{
		return m_sLocalInfo;
	}
	ServerInfoOpt& GetRemoteServerInfo()
	{
		return m_sRemoteInfo;
	}

	ServerInfoOpt& GetClientServerInfo()
	{
		return m_sClientInfo;
	}

	DatabaseInfoOpt& GetDatabaseInfo()
	{
		ASSERT(m_eServerType == ESERVER_TYPE_DP);
		return m_sDbInfo;	
	}

private:

	EServerType m_eServerType;

	ServerInfoOpt m_sLocalInfo;
	ServerInfoOpt m_sRemoteInfo;
	ServerInfoOpt m_sClientInfo;
	DatabaseInfoOpt m_sDbInfo;

};




#endif