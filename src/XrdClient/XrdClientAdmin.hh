//////////////////////////////////////////////////////////////////////////
//                                                                      //
// XrdClientAdmin                                                       //
//                                                                      //
// Author: Fabrizio Furano (INFN Padova, 2004)                          //
// Adapted from TXNetFile (root.cern.ch) originally done by             //
//  Alvise Dorigo, Fabrizio Furano                                      //
//          INFN Padova, 2003                                           //
//                                                                      //
// A UNIX reference admin client for xrootd.                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//       $Id$

#ifndef XRD_CLIENT_ADMIN_H
#define XRD_CLIENT_ADMIN_H


#include "XrdClient/XrdClientAbs.hh"
#include "XrdClient/XrdClientVector.hh"
#include "XrdOuc/XrdOucHash.hh"
#include "XrdOuc/XrdOucString.hh"


typedef XrdClientVector<XrdOucString> vecString;
typedef XrdClientVector<bool> vecBool;

void joinStrings(XrdOucString &buf, vecString vs);

class XrdClientAdmin : public XrdClientAbs {

   XrdOucString                    fInitialUrl;
   static XrdOucHash<XrdClientAdmin> fgAdminHash;

 protected:

   bool                            CanRedirOnError() {
     // We deny any redir on error
     return false;
   }

   // To be called after a redirection
   bool                            OpenFileWhenRedirected(char *, bool &);

 public:
   XrdClientAdmin(const char *url);
   virtual ~XrdClientAdmin();

   bool                            Connect();

   // Some administration functions, see the protocol specs for details
   bool                            SysStatX(const char *paths_list,
                                            kXR_char *binInfo);

   bool                            Stat(const char *fname,
                                        long &id,
                                        long long &size,
                                        long &flags,
                                        long &modtime);

   bool                            DirList(const char *dir,
                                           vecString &);

   bool                            ExistFiles(vecString&,
                                              vecBool&);

   bool                            ExistDirs(vecString&,
                                             vecBool&);

   long                            GetChecksum(kXR_char *path,
                                               kXR_char **chksum);

   bool                            IsFileOnline(vecString&,
                                                vecBool&);

   bool                            Mv(const char *fileSrc,
                                      const char *fileDest);

   bool                            Mkdir(const char *dir,
                                         int user,
                                         int group,
                                         int other);

   bool                            Chmod(const char *file,
                                         int user,
                                         int group,
                                         int other);

   bool                            Rm(const char *file);

   bool                            Rmdir(const char *path);

   bool                            Protocol(kXR_int32 &proto,
                                            kXR_int32 &kind);

   bool                            Prepare(vecString vs,
                                           kXR_char opts,
                                           kXR_char prty);
   bool                            Prepare(const char *paths,
                                           kXR_char opts,
                                           kXR_char prty);

   // Gives ONE location of a particular file... if present
   bool                            Locate(kXR_char *pathfile,
		                          XrdClientUrlInfo &urlinfo);
	   
   UnsolRespProcResult             ProcessUnsolicitedMsg(XrdClientUnsolMsgSender *sender,
                                                         XrdClientMessage *unsolmsg);

   // Hook to the open connection (needed by TXNetSystem)
   XrdClientConn                  *GetClientConn() const { return fConnModule; }

   // Checks if an admin already exists for url
   static XrdClientAdmin          *GetClientAdmin(const char *url);
};

#endif





