/* $NoKeywords:$ */
/**
 * @file
 *
 *  Family specific PCIe PHY initialization services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 40760 $   @e \$Date: 2010-10-27 08:55:23 +0800 (Wed, 27 Oct 2010) $
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
 * 
 * ***************************************************************************
 *
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "AGESA.h"
#include  "Ids.h"
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  GNB_MODULE_DEFINITIONS (GnbCommonLib)
#include  GNB_MODULE_DEFINITIONS (GnbPcieInitLibV1)
#include  "PcieFamilyServices.h"
#include  "GnbRegistersON.h"
#include  "Filecode.h"
#define FILECODE PROC_GNB_PCIE_FAMILY_0X14_F14PCIEPIFSERVICES_FILECODE
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
 * Set PLL mode for L1
 *
 *
 * @param[in]  LaneBitmap  Power down PLL for these lanes
 * @param[in]  Wrapper     Pointer to Wrapper config descriptor
 * @param[in]  Pcie        Pointer to PICe configuration data area
 */
VOID
PcieFmPifSetPllModeForL1 (
  IN      UINT32                LaneBitmap,
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32  ActiveLaneBitmap;
  ActiveLaneBitmap = PcieUtilGetWrapperLaneBitMap (LANE_TYPE_PCIE_ACTIVE | LANE_TYPE_PCIE_HOTPLUG, 0, Wrapper, Pcie);
  // This limits PLL setting to be identical for all PLL on wrapper.
  if ((ActiveLaneBitmap & LaneBitmap) == ActiveLaneBitmap) {
    LaneBitmap &= PcieUtilGetWrapperLaneBitMap (LANE_TYPE_PCIE_ALL, 0, Wrapper, Pcie);
    PciePifSetPllModeForL1 (LaneBitmap, Wrapper, Pcie);
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * PLL power up latency
 *
 *
 * @param[in]  Wrapper     Pointer to Wrapper config descriptor
 * @param[in]  Pcie        Pointer to PICe configuration data area
 * @retval                 Pll wake up latency in us
 */
UINT8
PcieFmPifGetPllPowerUpLatency (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  return 30;
}
