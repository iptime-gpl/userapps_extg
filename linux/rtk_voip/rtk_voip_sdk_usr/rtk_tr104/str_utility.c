#include <string.h>
#include <stdlib.h>
#include "str_utility.h"

static const char *GetObjectInstanceNumber( const char *pszFullName, const char *pszShortName, unsigned int *pInstNumber )
{
	/*
	 * pszFullName: 'aaaaa.bbbb.cccc.xxxxx.1.yyyy'
	 * pszShortName: '.xxxxx.'
	 * --> retrieve '1'
	 */
	const char *pszSubstr;

	/* pszSubstr will point to '.xxxxxx.' of full name */
	if( ( pszSubstr = strstr( pszFullName, pszShortName ) ) == NULL )
		return NULL;
	
	/* make pszSubstr to point to '1' */
	pszSubstr += strlen( pszShortName );
	
	*pInstNumber = atoi( pszSubstr );
	
	if( *pInstNumber == 0 )	/* This is a one-based system. */
		return NULL;

	return pszSubstr;
}

const char *GetOneBasedInstanceNumber_Capabilities_Codecs( 
										const char *pszFullName, 
										unsigned int *pInstNumber )
{
	/* .VoiceService.{i}.Capabilities.Codecs.{i}. */
	return GetObjectInstanceNumber( pszFullName, ".Codecs.", pInstNumber );
}

const char *GetOneBasedInstanceNumber_VoiceProfile( 
										const char *pszFullName, 
										unsigned int *pInstNumber )
{
	/* .VoiceService.{i}.VoiceProfile.{i}. */
	return GetObjectInstanceNumber( pszFullName, ".VoiceProfile.", pInstNumber );
}

const char *GetOneBasedInstanceNumber_PhyInterface( 
										const char *pszFullName, 
										unsigned int *pInstNumber )
{
	/* .VoiceService.{i}.PhyInterface.{i}. */
	return GetObjectInstanceNumber( pszFullName, ".PhyInterface.", pInstNumber );
}

const char *GetOneBasedInstanceNumber_VoiceProfile_Line( 
								const char *pszFullName, 
								unsigned int *pInstNumber_VoiceProfile,
								unsigned int *pInstNumber_Line )
{
	/* .VoiceService.{i}.VoiceProfile.{i}.Line.{i}. */
	const char *pszIntermediate;
	
	if( !( pszIntermediate = 
		GetOneBasedInstanceNumber_VoiceProfile( pszFullName, pInstNumber_VoiceProfile ) ) )
	{
		return NULL;
	}
	
	return GetObjectInstanceNumber( pszIntermediate, ".Line.", pInstNumber_Line );
}

const char *GetOneBasedInstanceNumber_PhyInterface_PoorQualityList( 
								const char *pszFullName, 
								unsigned int *pInstNumber_PhyInterface,
								unsigned int *pInstNumber_PoorQualityList )
{
	/* .VoiceService.{i}.PhyInterface.{i}.X_ CT-COM_Stats.PoorQualityList.{i}.  */
	const char *pszIntermediate;
	
	if( !( pszIntermediate = 
		GetOneBasedInstanceNumber_VoiceProfile( pszFullName, pInstNumber_PhyInterface ) ) )
	{
		return NULL;
	}
	
	return GetObjectInstanceNumber( pszIntermediate, ".PoorQualityList.", pInstNumber_PoorQualityList );
}

const char *GetOneBasedInstanceNumber_VoiceProfile_Line_List( 
								const char *pszFullName, 
								unsigned int *pInstNumber_VoiceProfile,
								unsigned int *pInstNumber_Line,
								unsigned int *pInstNumber_List )
{
	/* .VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Codec.List.{i} */
	const char *pszIntermediate;
	
	if( !( pszIntermediate =
		GetOneBasedInstanceNumber_VoiceProfile_Line( pszFullName, 
													 pInstNumber_VoiceProfile, 
													 pInstNumber_Line ) ) )
	{
		return NULL;
	}
	
	return GetObjectInstanceNumber( pszIntermediate, ".List.", pInstNumber_List );
}

const char *GetOneBasedInstanceNumber_VoiceProfile_Line_Session( 
								const char *pszFullName, 
								unsigned int *pInstNumber_VoiceProfile,
								unsigned int *pInstNumber_Line,
								unsigned int *pInstNumber_List )
{
	/* .VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Session.{i} */
	const char *pszIntermediate;

	if( !( pszIntermediate =
		GetOneBasedInstanceNumber_VoiceProfile_Line( pszFullName, 
													 pInstNumber_VoiceProfile, 
													 pInstNumber_Line ) ) )
	{
		return NULL;
	}

	return GetObjectInstanceNumber( pszIntermediate, ".Session.", pInstNumber_List );
}

const char *GetOneBasedInstanceNumber_VoiceProfile_NumberingPlan_PrefixInfo( 
								const char *pszFullName, 
								unsigned int *pInstNumber_VoiceProfile,
								unsigned int *pInstNumber_Line )
{
	/* .Services.VoiceService.{i}.VoiceProfile.{i}.NumberingPlan.PrefixInfo.{i}. */
	const char *pszIntermediate;
	
	if( !( pszIntermediate = 
		GetOneBasedInstanceNumber_VoiceProfile( pszFullName, pInstNumber_VoiceProfile ) ) )
	{
		return NULL;
	}
	
	return GetObjectInstanceNumber( pszIntermediate, ".PrefixInfo.", pInstNumber_Line );
}
