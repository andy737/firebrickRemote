/* $NoKeywords:$ */
/**
 * @file
 *
 * Interface to initialize Graphics Controller at POST
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 48452 $   @e \$Date: 2011-03-09 12:50:44 +0800 (Wed, 09 Mar 2011) $
 *
 */
/*
*****************************************************************************
*
* Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of 
 *       its contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ***************************************************************************
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "AGESA.h"
#include  "amdlib.h"
#include  "Ids.h"
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbGfx.h"
#include  "GnbGfxInitLibV1.h"
#include  "GnbGfxConfig.h"
#include  "GfxStrapsInit.h"
#include  "GfxLib.h"
#include  "GfxConfigData.h"
#include  "GfxInitAtPost.h"
#include  "Filecode.h"
#define FILECODE PROC_GNB_GFX_GFXINITATPOST_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Init GFX at Post.
 *
 *
 *
 * @param[in]     StdHeader     Standard configuration header
 * @retval        AGESA_STATUS
 */


AGESA_STATUS
GfxInitAtPost (
  IN       AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AMD_POST_PARAMS       *PostParamsPtr;
  AGESA_STATUS          Status;
  GFX_PLATFORM_CONFIG   *Gfx;
  PostParamsPtr = (AMD_POST_PARAMS *)StdHeader;
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxInitAtPost Enter\n");
  Status = GfxLocateConfigData (StdHeader, &Gfx);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    if (GfxLibIsControllerPresent (StdHeader)) {
      if (PostParamsPtr->MemConfig.UmaMode != UMA_NONE) {
        GfxGetDiscreteCardInfo (&Gfx->GfxDiscreteCardInfo, StdHeader);
        if (Gfx->GfxDiscreteCardInfo.PciGfxCardBitmap != 0 ||
           (Gfx->GfxDiscreteCardInfo.AmdPcieGfxCardBitmap & Gfx->GfxDiscreteCardInfo.PcieGfxCardBitmap) !=
            Gfx->GfxDiscreteCardInfo.PcieGfxCardBitmap) {
          PostParamsPtr->MemConfig.UmaMode = UMA_NONE;
          IDS_HDT_CONSOLE (GFX_MISC, "  GfxDisabled due to dGPU policy\n");
        }
      }
    } else {
      PostParamsPtr->MemConfig.UmaMode = UMA_NONE;
      Gfx->GfxFusedOff = TRUE;
    }
  } else {
    PostParamsPtr->MemConfig.UmaMode = UMA_NONE;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxInitAtPost Exit [0x%x]\n", Status);
  return  Status;
}
